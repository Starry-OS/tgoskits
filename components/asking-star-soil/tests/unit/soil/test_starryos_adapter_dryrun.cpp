#include "asking_star/soil/adapters/starryos_adapter.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>
#include <string>

namespace {

asking_star::soil::KernelRequest request_for(
    asking_star::soil::OperationKind operation) {
  asking_star::soil::SoilRuntime soil;
  return soil.make_request(asking_star::tests::soil::make_soil_test_cell(),
                           operation, "starryos.target", "payload");
}

}  // namespace

int main() {
  asking_star::soil::adapters::StarryOSAdapter dryrun{
      {false, asking_star::soil::adapters::StarryOSAdapterMode::DryRun}};

  auto log = dryrun.execute(request_for(asking_star::soil::OperationKind::LogWrite));
  assert(log.ok());
  assert(log.message.find("dry-run") != std::string::npos);

  auto uart =
      dryrun.execute(request_for(asking_star::soil::OperationKind::UartWrite));
  assert(uart.ok());

  auto ioctl = dryrun.execute(
      request_for(asking_star::soil::OperationKind::DeviceIoctl));
  assert(ioctl.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);

  asking_star::soil::adapters::StarryOSAdapter board{
      {true, asking_star::soil::adapters::StarryOSAdapterMode::BoardReal}};
  auto board_result =
      board.execute(request_for(asking_star::soil::OperationKind::LogWrite));
  assert(board_result.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);
  return 0;
}
