#include "asking_star/v55/qemu_report_bridge.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::filesystem::path make_qemu_report_fixture() {
  const auto dir = std::filesystem::temp_directory_path() /
                   "asking-star-v55-qemu-report-fixture";
  std::filesystem::create_directories(dir);
  {
    std::ofstream report(dir / "boot-report.md");
    report << "# Star Sentinel Boot Report\n";
    report << "- Final boot state: `BOOT_SUCCESS`\n";
    report << "- Shell ready: `True`\n";
    report << "- QEMU command: `bash scripts/run-qemu.sh`\n";
  }
  {
    std::ofstream events(dir / "boot-events.jsonl");
    events << "{\"type\":\"handler.started\",\"payload\":{\"handler\":"
              "\"qemu_launch\"}}\n";
  }
  {
    std::ofstream serial(dir / "serial.log");
    serial << "Starting QEMU. Exit with Ctrl+A then X.\n";
    serial << "StarryOS dry-run serial marker\n";
    serial << "/ #\n";
  }
  return dir;
}

}  // namespace

int main() {
  using asking_star::core::kernelsoil::QemuDryRunSoilAdapter;
  using asking_star::core::kernelsoil::QemuObservationConfig;
  using asking_star::v55::AdapterMode;
  using asking_star::v55::ChamberExecutionRecord;
  using asking_star::v55::QemuReportBridge;

  const auto fixture = make_qemu_report_fixture();
  QemuDryRunSoilAdapter adapter;
  const auto observation =
      adapter.observe(QemuObservationConfig{fixture});
  assert(observation.is_valid());
  assert(observation.boot_success);
  assert(observation.shell_ready);

  const ChamberExecutionRecord execution{110, 55, AdapterMode::DryRun,
                                         "observe qemu dry-run"};
  const QemuReportBridge bridge;
  const auto projected = bridge.project(execution, observation);
  assert(projected.source_is_qemu_dry_run);
  assert(!projected.board_real_claim);
  assert(projected.pouch.health == "healthy");
  assert(projected.pouch.output.find("source_mode=qemu_dry_run") !=
         std::string::npos);
  assert(projected.skin.trace_status == "qemu-observed");
  assert(projected.skin.adapter_mode == AdapterMode::DryRun);
  assert(!projected.skin.reflex_hit);

  return 0;
}
