#include "core/kernelsoil/qemu_dry_run_soil_adapter.h"

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

using asking_star::core::charge::ChargeId;
using asking_star::core::charge::GateDecision;
using asking_star::core::charge::GateDecisionKind;
using asking_star::core::charge::GateDecisionTrace;
using asking_star::core::kernelsoil::QemuDryRunSoilAdapter;
using asking_star::core::kernelsoil::QemuObservationConfig;
using asking_star::core::kernelsoil::SoilOperation;
using asking_star::core::kernelsoil::SoilRequest;

std::filesystem::path make_fixture_dir() {
  auto dir = std::filesystem::temp_directory_path() /
             "asking-star-qemu-dry-run-fixture";
  std::filesystem::create_directories(dir);
  {
    std::ofstream report(dir / "boot-report.md");
    report << "# Star Sentinel Boot Report\n";
    report << "- Final boot state: `BOOT_SUCCESS`\n";
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
  }
  return dir;
}

SoilRequest make_request(GateDecisionKind kind = GateDecisionKind::Pass) {
  return SoilRequest{
      "soil-qemu-observe",
      SoilOperation::DriverSerialWrite,
      GateDecisionTrace{
          "gate-qemu-observe",
          ChargeId{"charge-qemu-observe"},
          GateDecision{kind, 1.0, 1.0, "charge passed gate"}},
      "observe StarryOS QEMU serial output",
      "route-qemu-observe"};
}

bool trace_contains(const std::vector<std::string>& trace,
                    const std::string& needle) {
  for (const auto& line : trace) {
    if (line.find(needle) != std::string::npos) {
      return true;
    }
  }
  return false;
}

void test_qemu_dry_run_observes_boot_supervisor_outputs() {
  const auto fixture = make_fixture_dir();
  QemuDryRunSoilAdapter adapter;

  const auto result =
      adapter.dispatch_observed(make_request(), QemuObservationConfig{fixture});

  assert(result.is_valid());
  assert(result.status == "qemu-observed");
  assert(result.dry_run);
  assert(trace_contains(result.trace, "charge_id=charge-qemu-observe"));
  assert(trace_contains(result.trace, "route_id=route-qemu-observe"));
  assert(trace_contains(result.trace, "qemu_started=true"));
  assert(trace_contains(result.trace, "serial_observed=true"));
  assert(trace_contains(result.trace, "boot_state=BOOT_SUCCESS"));
}

void test_qemu_dry_run_keeps_kernel_and_genebank_read_only() {
  QemuDryRunSoilAdapter adapter;

  assert(!adapter.executes_real_kernel());
  assert(!adapter.writes_genebank());
}

void test_blocked_gate_does_not_consume_qemu_observation() {
  const auto fixture = make_fixture_dir();
  QemuDryRunSoilAdapter adapter;

  const auto result = adapter.dispatch_observed(
      make_request(GateDecisionKind::Freeze), QemuObservationConfig{fixture});

  assert(result.status == "blocked");
  assert(trace_contains(result.trace, "blocked by gate"));
}

void test_optional_real_boot_supervisor_report_observation() {
  const char* report_dir = std::getenv("ASKING_STAR_STARRYOS_REPORTS");
  if (report_dir == nullptr || std::string{report_dir}.empty()) {
    return;
  }

  QemuDryRunSoilAdapter adapter;
  const auto result = adapter.dispatch_observed(
      make_request(), QemuObservationConfig{std::filesystem::path{report_dir}});

  assert(result.is_valid());
  assert(result.status == "qemu-observed");
  assert(trace_contains(result.trace, "qemu_started=true") ||
         trace_contains(result.trace, "serial_observed=true"));
}

}  // namespace

int main() {
  test_qemu_dry_run_observes_boot_supervisor_outputs();
  test_qemu_dry_run_keeps_kernel_and_genebank_read_only();
  test_blocked_gate_does_not_consume_qemu_observation();
  test_optional_real_boot_supervisor_report_observation();
  return 0;
}
