#pragma once

#include "asking_star/v55/chamber_pouch.hpp"
#include "asking_star/v55/chamber_runtime.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace asking_star::v55 {

enum class RknnProbeStatus {
  MissingRuntime,
  RuntimeFound,
  ToolchainFound,
  HostDryRunReady,
  LinuxGoldenPass,
};

struct RknnRuntimeProbeRecord {
  std::string runtime_path;
  std::string model_path;
  std::string toolchain_path;
  RknnProbeStatus status{RknnProbeStatus::MissingRuntime};
  std::vector<std::string> evidence;
  bool host_probe_ok{false};
  bool host_npu_run_claim{false};
  bool starryos_run_claim{false};
};

struct RknnTensorIoRecord {
  std::string input_shape;
  std::string output_shape;
  std::string tensor_hash;
  bool real_npu_tensor{false};
};

struct RknnExecutionTraceRecord {
  RknnRuntimeProbeRecord probe;
  RknnTensorIoRecord tensor_io;
  ChamberPouchRecord pouch;
  std::vector<std::string> starryos_gap_list;
};

struct RknnLinuxGoldenRecord {
  std::filesystem::path board_pull_dir;
  std::string board_uname;
  std::string board_compatible;
  std::string runtime_path;
  std::string runtime_build_id;
  std::string model_path;
  std::string model_size;
  std::string sdk_api_version;
  std::string sdk_drv_version;
  std::string input_shape;
  std::string output_shape;
  std::string output_total_bytes;
  std::string latency_us_host;
  std::string latency_us_rknn;
  std::string final_status;
  std::string output_sha256;
  bool librknnrt_present{false};
  bool dma_heap_present{false};
  bool linux_golden_pass{false};
  bool host_npu_run_claim{false};
  bool starryos_run_claim{false};
};

[[nodiscard]] inline const char* to_string(RknnProbeStatus status) {
  switch (status) {
    case RknnProbeStatus::MissingRuntime:
      return "missing_runtime";
    case RknnProbeStatus::RuntimeFound:
      return "runtime_found";
    case RknnProbeStatus::ToolchainFound:
      return "toolchain_found";
    case RknnProbeStatus::HostDryRunReady:
      return "host_dryrun_ready";
    case RknnProbeStatus::LinuxGoldenPass:
      return "linux_golden_pass";
  }
  return "missing_runtime";
}

class LinuxRknnRuntimeChamber {
 public:
  [[nodiscard]] RknnRuntimeProbeRecord probe_from_env() const {
    return probe(read_env("ASKING_STAR_RKNNRT_SO"),
                 read_env("ASKING_STAR_RKNN_MODEL"),
                 read_env("ASKING_STAR_RKNN_TOOLCHAIN"));
  }

  [[nodiscard]] RknnRuntimeProbeRecord probe(std::string runtime_path,
                                             std::string model_path,
                                             std::string toolchain_path) const {
    RknnRuntimeProbeRecord record;
    record.runtime_path = std::move(runtime_path);
    record.model_path = std::move(model_path);
    record.toolchain_path = std::move(toolchain_path);

    if (record.runtime_path.empty() ||
        !std::filesystem::exists(record.runtime_path)) {
      record.status = RknnProbeStatus::MissingRuntime;
      record.evidence.push_back("missing_runtime");
      record.starryos_run_claim = false;
      record.host_npu_run_claim = false;
      return record;
    }

    record.status = RknnProbeStatus::RuntimeFound;
    record.host_probe_ok = true;
    record.evidence.push_back("runtime_path=" + record.runtime_path);
    record.evidence.push_back(
        "runtime_size=" +
        std::to_string(std::filesystem::file_size(record.runtime_path)));

    if (!record.toolchain_path.empty() &&
        std::filesystem::exists(record.toolchain_path)) {
      record.status = RknnProbeStatus::ToolchainFound;
      record.evidence.push_back("toolchain_path=" + record.toolchain_path);
    }
    if (!record.model_path.empty() && std::filesystem::exists(record.model_path)) {
      record.status = RknnProbeStatus::HostDryRunReady;
      record.evidence.push_back("model_path=" + record.model_path);
    }
    record.host_npu_run_claim = false;
    record.starryos_run_claim = false;
    return record;
  }

  [[nodiscard]] RknnExecutionTraceRecord build_trace(
      const RknnRuntimeProbeRecord& probe,
      const RknnTensorIoRecord& tensor_io) const {
    RknnExecutionTraceRecord trace;
    trace.probe = probe;
    trace.tensor_io = tensor_io;
    ChamberExecutionRecord execution{9000, 1, AdapterMode::Host,
                                     to_string(probe.status)};
    ChamberPouchView pouch_view;
    trace.pouch = pouch_view.observe(execution, to_string(probe.status),
                                     probe.host_probe_ok);
    trace.starryos_gap_list = {
        "dynamic_linking_or_static_port",
        "rknpu_device_node_and_driver_abi",
        "dma_or_zero_copy_buffer",
        "cache_flush_and_memory_mapping",
        "threading_and_sync_primitives",
        "filesystem_model_and_runtime_assets",
    };
    return trace;
  }

  [[nodiscard]] RknnLinuxGoldenRecord import_linux_golden(
      const std::filesystem::path& board_pull_dir) const {
    RknnLinuxGoldenRecord record;
    record.board_pull_dir = board_pull_dir;

    const auto env_text =
        read_file(board_pull_dir / "output_env" / "env_probe.log");
    const auto trace_text =
        read_file(board_pull_dir / "output_v2" / "golden_trace.log");
    const auto manifest_text =
        read_file(board_pull_dir / "output_v2" / "golden_manifest.json");
    const auto artifacts_text =
        read_file(board_pull_dir / "artifacts.sha256");

    const auto trace_kv = parse_key_values(trace_text);
    record.board_uname = value_after_prefix(env_text, "uname=");
    record.board_compatible =
        block_first_non_empty(env_text, "compatible_begin", "compatible_end");
    record.runtime_path = value_between(trace_text, "librknnrt.so => ", " ");
    if (record.runtime_path.empty()) {
      record.runtime_path = value_after_prefix(env_text, "\tlibrknnrt.so ");
    }
    record.runtime_build_id = value_after_prefix(trace_text, "BuildID[sha1]=");
    record.model_path = map_value(trace_kv, "model_path");
    record.model_size = map_value(trace_kv, "model_size");
    record.sdk_api_version = map_value(trace_kv, "sdk_api_version");
    record.sdk_drv_version = map_value(trace_kv, "sdk_drv_version");
    record.input_shape = map_value(trace_kv, "input0_dims");
    record.output_shape = map_value(trace_kv, "output0_dims");
    record.output_total_bytes = map_value(trace_kv, "output_total_bytes");
    record.latency_us_host = map_value(trace_kv, "latency_us_host");
    record.latency_us_rknn = map_value(trace_kv, "latency_us_rknn");
    record.final_status = map_value(trace_kv, "final_status");
    record.output_sha256 = sha_for(artifacts_text, "golden_output_0.bin");
    record.librknnrt_present =
        env_text.find("librknnrt.so") != std::string::npos ||
        trace_text.find("librknnrt.so") != std::string::npos;
    record.dma_heap_present =
        env_text.find("/dev/dma_heap") != std::string::npos;
    record.linux_golden_pass =
        record.final_status == "linux_golden_pass" &&
        manifest_text.find("\"starryos_used\": false") != std::string::npos &&
        manifest_text.find("\"starryos_npu_hal_used\": false") !=
            std::string::npos &&
        manifest_text.find("\"starryos_rknpu_driver_used\": false") !=
            std::string::npos;
    record.host_npu_run_claim = record.linux_golden_pass;
    record.starryos_run_claim = false;
    return record;
  }

 private:
  [[nodiscard]] static std::string read_env(const char* name) {
    const char* value = std::getenv(name);
    return value == nullptr ? std::string{} : std::string{value};
  }

  [[nodiscard]] static std::string read_file(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
      return {};
    }
    std::ostringstream out;
    out << in.rdbuf();
    return out.str();
  }

  [[nodiscard]] static std::map<std::string, std::string> parse_key_values(
      const std::string& text) {
    std::map<std::string, std::string> values;
    std::istringstream lines(text);
    std::string line;
    while (std::getline(lines, line)) {
      const auto pos = line.find('=');
      if (pos == std::string::npos || pos == 0) {
        continue;
      }
      values[line.substr(0, pos)] = line.substr(pos + 1);
    }
    return values;
  }

  [[nodiscard]] static std::string map_value(
      const std::map<std::string, std::string>& values,
      const std::string& key) {
    const auto it = values.find(key);
    return it == values.end() ? std::string{} : it->second;
  }

  [[nodiscard]] static std::string value_after_prefix(const std::string& text,
                                                      const std::string& prefix) {
    const auto start = text.find(prefix);
    if (start == std::string::npos) {
      return {};
    }
    auto value = text.substr(start + prefix.size());
    const auto end = value.find('\n');
    if (end != std::string::npos) {
      value = value.substr(0, end);
    }
    if (!value.empty() && value.back() == '\r') {
      value.pop_back();
    }
    return value;
  }

  [[nodiscard]] static std::string block_first_non_empty(
      const std::string& text,
      const std::string& begin,
      const std::string& end) {
    const auto block_begin = text.find(begin);
    if (block_begin == std::string::npos) {
      return {};
    }
    const auto content_begin = text.find('\n', block_begin);
    if (content_begin == std::string::npos) {
      return {};
    }
    const auto block_end = text.find(end, content_begin);
    auto content = text.substr(content_begin + 1, block_end - content_begin - 1);
    std::istringstream lines(content);
    std::string line;
    while (std::getline(lines, line)) {
      if (!line.empty() && line.back() == '\r') {
        line.pop_back();
      }
      if (!line.empty()) {
        return line;
      }
    }
    return {};
  }

  [[nodiscard]] static std::string sha_for(const std::string& text,
                                           const std::string& file_name) {
    std::istringstream lines(text);
    std::string line;
    while (std::getline(lines, line)) {
      if (line.find(file_name) == std::string::npos) {
        continue;
      }
      const auto space = line.find(' ');
      return line.substr(0, space);
    }
    return {};
  }

  [[nodiscard]] static std::string value_between(const std::string& text,
                                                 const std::string& prefix,
                                                 const std::string& suffix) {
    const auto start = text.find(prefix);
    if (start == std::string::npos) {
      return {};
    }
    const auto value_start = start + prefix.size();
    const auto value_end = text.find(suffix, value_start);
    if (value_end == std::string::npos) {
      return text.substr(value_start);
    }
    return text.substr(value_start, value_end - value_start);
  }
};

}  // namespace asking_star::v55
