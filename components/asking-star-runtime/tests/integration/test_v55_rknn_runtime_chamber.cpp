#include "asking_star/v55/rknn_runtime_chamber.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::filesystem::path make_board_pull_fixture() {
  const auto root =
      std::filesystem::temp_directory_path() / "asking-star-rknn-board-pull";
  std::filesystem::create_directories(root / "output_env");
  std::filesystem::create_directories(root / "output_v2");
  {
    std::ofstream env(root / "output_env" / "env_probe.log");
    env << "uname=Linux orangepi5plus 5.10.110-rockchip-rk3588 aarch64\n";
    env << "compatible_begin\nrockchip,rk3588-orangepi-5-plus\ncompatible_end\n";
    env << "devices_begin\n/dev/dma_heap/system\n/dev/dma_heap/cma\n";
    env << "devices_end\nlibs_begin\n\tlibrknnrt.so (libc6,AArch64) => "
           "/lib/librknnrt.so\nlibs_end\n";
  }
  {
    std::ofstream trace(root / "output_v2" / "golden_trace.log");
    trace << "/tmp/a_track/bin/librknnrt.so: ELF 64-bit LSB shared object, "
             "ARM aarch64, BuildID[sha1]=4f5001b81d147d0db1f48e68fe87a6029caa2ccb, stripped\n";
    trace << "\tlibrknnrt.so => /tmp/a_track/bin/librknnrt.so "
             "(0x0000007f9ab30000)\n";
    trace << "model_path=/tmp/a_track/model/tennis.rknn\n";
    trace << "model_size=5919222\n";
    trace << "sdk_api_version=2.3.2 (429f97ae6b@2025-04-09T09:09:27)\n";
    trace << "sdk_drv_version=0.8.2\n";
    trace << "input0_dims=1x640x640x3\n";
    trace << "output0_dims=1x5x27600\n";
    trace << "output_total_bytes=552000\n";
    trace << "latency_us_host=98560\n";
    trace << "latency_us_rknn=98558\n";
    trace << "final_status=linux_golden_pass\n";
  }
  {
    std::ofstream manifest(root / "output_v2" / "golden_manifest.json");
    manifest << "{\n";
    manifest << "  \"starryos_used\": false,\n";
    manifest << "  \"starryos_npu_hal_used\": false,\n";
    manifest << "  \"starryos_rknpu_driver_used\": false\n";
    manifest << "}\n";
  }
  {
    std::ofstream sha(root / "artifacts.sha256");
    sha << "cefc16fc1e3881fbbc19bb041f63cf97c4928d1ed2f875809cf6054489fc18d8"
           "  ./output_v2/golden_output_0.bin\n";
  }
  return root;
}

}  // namespace

int main() {
  using asking_star::v55::ChamberKind;
  using asking_star::v55::LinuxRknnRuntimeChamber;
  using asking_star::v55::RknnProbeStatus;
  using asking_star::v55::RknnTensorIoRecord;
  using asking_star::v55::default_chamber_profiles;
  using asking_star::v55::to_string;

  const auto defaults = default_chamber_profiles();
  assert(!defaults.empty());
  assert(defaults.front().kind == ChamberKind::LinuxRknnRuntime);

  LinuxRknnRuntimeChamber chamber;
  const auto missing = chamber.probe("missing-librknnrt.so", "", "");
  assert(missing.status == RknnProbeStatus::MissingRuntime);
  assert(!missing.host_probe_ok);
  assert(!missing.host_npu_run_claim);
  assert(!missing.starryos_run_claim);
  assert(std::string{to_string(missing.status)} == "missing_runtime");

  const auto runtime_path =
      std::filesystem::temp_directory_path() / "asking-star-librknnrt.so";
  {
    std::ofstream runtime(runtime_path);
    runtime << "fake rknn runtime for host probe metadata only\n";
  }
  const auto found = chamber.probe(runtime_path.string(), "", "");
  assert(found.status == RknnProbeStatus::RuntimeFound);
  assert(found.host_probe_ok);
  assert(!found.host_npu_run_claim);
  assert(!found.starryos_run_claim);

  const RknnTensorIoRecord tensor{"1x3x224x224", "1x1000",
                                  "tensor-sha256-demo", false};
  const auto trace = chamber.build_trace(found, tensor);
  assert(trace.pouch.health == "healthy");
  assert(!trace.tensor_io.real_npu_tensor);
  assert(trace.starryos_gap_list.size() >= 6);

  const auto fixture = make_board_pull_fixture();
  const auto golden = chamber.import_linux_golden(fixture);
  assert(golden.linux_golden_pass);
  assert(golden.host_npu_run_claim);
  assert(!golden.starryos_run_claim);
  assert(golden.librknnrt_present);
  assert(golden.dma_heap_present);
  assert(golden.runtime_path == "/tmp/a_track/bin/librknnrt.so");
  assert(golden.sdk_api_version.find("2.3.2") != std::string::npos);
  assert(golden.sdk_drv_version == "0.8.2");
  assert(golden.input_shape == "1x640x640x3");
  assert(golden.output_shape == "1x5x27600");
  assert(golden.output_sha256.find("cefc16fc") == 0);

  const std::filesystem::path local_board_pull{
      "/mnt/d/proj/starryos-merged/golden/a_track/output/"
      "board_pull_20260627_215440"};
  if (std::filesystem::exists(local_board_pull)) {
    const auto local = chamber.import_linux_golden(local_board_pull);
    assert(local.linux_golden_pass);
    assert(local.host_npu_run_claim);
    assert(!local.starryos_run_claim);
    assert(local.sdk_api_version.find("2.3.2") != std::string::npos);
    assert(local.sdk_drv_version == "0.8.2");
    assert(local.output_total_bytes == "552000");
  }

  std::filesystem::remove(runtime_path);
  return 0;
}
