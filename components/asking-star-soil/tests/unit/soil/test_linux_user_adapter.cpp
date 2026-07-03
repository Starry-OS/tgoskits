#include "asking_star/soil/adapters/linux_user_adapter.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>
#include <string>
#include <utility>

namespace {

asking_star::soil::KernelRequest make_request(
    asking_star::soil::OperationKind operation, std::string target,
    std::string payload = "payload") {
  asking_star::soil::SoilRuntime soil;
  return soil.make_request(asking_star::tests::soil::make_soil_test_cell(),
                           operation, std::move(target), std::move(payload));
}

}  // namespace

int main() {
  asking_star::soil::adapters::LinuxUserAdapter adapter{"runtime_tmp/round14"};

  auto log = adapter.execute(
      make_request(asking_star::soil::OperationKind::LogWrite, "stdout",
                   "log payload"));
  assert(log.ok());

  auto write = adapter.execute(
      make_request(asking_star::soil::OperationKind::FileWrite, "sample.txt",
                   "file payload"));
  assert(write.ok());

  auto read = adapter.execute(
      make_request(asking_star::soil::OperationKind::FileRead, "sample.txt"));
  assert(read.ok());
  assert(read.payload == "file payload");

  auto unsafe = adapter.execute(
      make_request(asking_star::soil::OperationKind::FileWrite,
                   "../CMakeLists.txt", "bad"));
  assert(unsafe.status == asking_star::soil::SoilExecutionStatus::Rejected);

  auto uart = adapter.execute(
      make_request(asking_star::soil::OperationKind::UartWrite, "uart0"));
  assert(uart.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);

  auto ioctl = adapter.execute(
      make_request(asking_star::soil::OperationKind::DeviceIoctl, "device"));
  assert(ioctl.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);
  return 0;
}
