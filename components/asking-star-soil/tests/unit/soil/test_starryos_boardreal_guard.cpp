#include "asking_star/soil/adapters/starryos_adapter.hpp"
#include "asking_star/soil/return_rebuilder.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>
#include <string>

namespace {

asking_star::soil::KernelRequest make_request(
    asking_star::soil::OperationKind operation,
    const std::string& target,
    const std::string& payload) {
  asking_star::soil::SoilRuntime soil;
  return soil.make_request(asking_star::tests::soil::make_soil_test_cell(),
                           operation, target, payload);
}

}  // namespace

int main() {
  asking_star::soil::adapters::StarryOSAdapter adapter{
      {true, asking_star::soil::adapters::StarryOSAdapterMode::BoardReal}};

  auto log = adapter.execute(make_request(
      asking_star::soil::OperationKind::LogWrite, "starryos.console",
      "[AskingStar:UART] hello from V5 DigitalCell"));
  assert(log.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);
  assert(log.trace_id == "trace-soil");
  assert(log.message.find("unavailable") != std::string::npos);

  auto ioctl = adapter.execute(make_request(
      asking_star::soil::OperationKind::DeviceIoctl, "starryos.device",
      "must-not-run"));
  assert(ioctl.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);
  assert(ioctl.trace_id == "trace-soil");

  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  assert(rebuilder.rebuild(log, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == "trace-soil");
  assert(fragment.star_tag == "soil.kernel_result.error");

  return 0;
}
