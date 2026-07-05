#include "asking_star/soil/adapters/starryos_operation_map.hpp"

#include <cassert>

int main() {
  asking_star::soil::adapters::StarryOSOperationMap map;

  auto log = map.map(asking_star::soil::OperationKind::LogWrite);
  assert(log.dry_run_supported);
  assert(log.first_real_supported);

  auto uart = map.map(asking_star::soil::OperationKind::UartWrite);
  assert(uart.dry_run_supported);
  assert(uart.first_real_supported);

  auto ioctl = map.map(asking_star::soil::OperationKind::DeviceIoctl);
  assert(!ioctl.first_real_supported);
  assert(!ioctl.dry_run_supported);
  return 0;
}

