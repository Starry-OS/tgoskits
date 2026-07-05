#pragma once

#include "core/kernelsoil/soil_result.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace asking_star::core::kernelsoil {

struct QemuObservationConfig {
  std::filesystem::path report_dir;
  std::filesystem::path boot_report_path;
  std::filesystem::path boot_events_path;
  std::filesystem::path serial_log_path;

  [[nodiscard]] bool is_valid() const {
    return !report_dir.empty() || !boot_report_path.empty() ||
           !boot_events_path.empty() || !serial_log_path.empty();
  }
};

struct QemuObservation {
  bool qemu_started{false};
  bool serial_observed{false};
  bool boot_success{false};
  bool shell_ready{false};
  std::string final_boot_state;
  std::string boot_report_excerpt;
  std::string serial_excerpt;
  std::string serial_log;

  [[nodiscard]] bool is_valid() const {
    return qemu_started || serial_observed || !final_boot_state.empty();
  }
};

class QemuDryRunSoilAdapter {
 public:
  [[nodiscard]] QemuObservation observe(
      const QemuObservationConfig& config) const {
    const auto boot_report = read_file(resolve_boot_report(config));
    const auto boot_events = read_file(resolve_boot_events(config));
    const auto serial_log = read_file(resolve_serial_log(config));

    QemuObservation observation;
    observation.qemu_started =
        contains(boot_report, "QEMU command") ||
        contains(boot_events, "qemu_launch") ||
        contains(serial_log, "Starting QEMU");
    observation.serial_observed = !serial_log.empty();
    observation.boot_success = contains(boot_report, "BOOT_SUCCESS") ||
                               contains(boot_events, "BOOT_SUCCESS");
    observation.shell_ready =
        !contains(boot_report, "Shell ready: `False`") &&
        !contains(boot_report, "Shell ready: False") &&
        (contains(boot_report, "Shell ready: `True`") ||
         contains(boot_report, "Shell ready: True") ||
         contains(serial_log, "/ #") || contains(serial_log, "login:"));
    observation.final_boot_state = extract_final_boot_state(boot_report);
    observation.boot_report_excerpt = first_line(boot_report);
    observation.serial_excerpt = first_line(serial_log);
    observation.serial_log = serial_log;
    return observation;
  }

  [[nodiscard]] SoilResult dispatch_observed(
      const SoilRequest& request, const QemuObservationConfig& config) const {
    if (!request.is_valid()) {
      return {"invalid",
              "reject",
              0,
              {"invalid qemu dry-run request"},
              true,
              "INVALID_QEMU_DRY_RUN_REQUEST",
              "invalid-qemu-dry-run",
              ExecutionMode::Qemu};
    }
    if (!request.can_dispatch()) {
      return {request.id,
              "blocked",
              0,
              {"blocked by gate: " + request.gate_trace.decision.reason},
              true,
              "GATE_BLOCKED",
              request.trace_id(),
              request.mode};
    }

    const auto observation = observe(config);
    std::vector<std::string> trace{
        "charge_id=" + request.gate_trace.charge_id.value,
        "route_id=" + request.route_id,
        "gate_decision=" + request.gate_trace.decision.reason,
        "qemu_started=" + bool_text(observation.qemu_started),
        "serial_observed=" + bool_text(observation.serial_observed),
        "boot_success=" + bool_text(observation.boot_success),
        "shell_ready=" + bool_text(observation.shell_ready),
        "boot_state=" + observation.final_boot_state,
    };
    if (!observation.serial_excerpt.empty()) {
      trace.push_back("serial_excerpt=" + observation.serial_excerpt);
    }
    if (!observation.boot_report_excerpt.empty()) {
      trace.push_back("boot_report_excerpt=" +
                      observation.boot_report_excerpt);
    }

    return {request.id,
            observation.is_valid() ? "qemu-observed" : "qemu-not-observed",
            0,
            trace,
            true,
            observation.is_valid() ? "" : "QEMU_NOT_OBSERVED",
            request.trace_id(),
            ExecutionMode::Qemu};
  }

  [[nodiscard]] bool executes_real_kernel() const { return false; }

  [[nodiscard]] bool writes_genebank() const { return false; }

 private:
  [[nodiscard]] static std::filesystem::path resolve_boot_report(
      const QemuObservationConfig& config) {
    if (!config.boot_report_path.empty()) {
      return config.boot_report_path;
    }
    return config.report_dir / "boot-report.md";
  }

  [[nodiscard]] static std::filesystem::path resolve_boot_events(
      const QemuObservationConfig& config) {
    if (!config.boot_events_path.empty()) {
      return config.boot_events_path;
    }
    return config.report_dir / "boot-events.jsonl";
  }

  [[nodiscard]] static std::filesystem::path resolve_serial_log(
      const QemuObservationConfig& config) {
    if (!config.serial_log_path.empty()) {
      return config.serial_log_path;
    }
    return config.report_dir / "serial.log";
  }

  [[nodiscard]] static std::string read_file(const std::filesystem::path& path) {
    if (path.empty()) {
      return {};
    }
    std::ifstream input(path);
    if (!input) {
      return {};
    }
    std::ostringstream out;
    out << input.rdbuf();
    return out.str();
  }

  [[nodiscard]] static bool contains(const std::string& text,
                                     const std::string& needle) {
    return text.find(needle) != std::string::npos;
  }

  [[nodiscard]] static std::string first_line(const std::string& text) {
    const auto end = text.find('\n');
    auto line = text.substr(0, end == std::string::npos ? text.size() : end);
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }
    return line;
  }

  [[nodiscard]] static std::string extract_final_boot_state(
      const std::string& boot_report) {
    const std::string prefix = "Final boot state: `";
    const auto start = boot_report.find(prefix);
    if (start == std::string::npos) {
      return "unknown";
    }
    const auto value_start = start + prefix.size();
    const auto value_end = boot_report.find('`', value_start);
    if (value_end == std::string::npos) {
      return "unknown";
    }
    return boot_report.substr(value_start, value_end - value_start);
  }

  [[nodiscard]] static std::string bool_text(bool value) {
    return value ? "true" : "false";
  }
};

}  // namespace asking_star::core::kernelsoil
