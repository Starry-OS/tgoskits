#include "asking_star/v55/chamber_starryos_dryrun_bridge.hpp"

#include <cassert>
#include <string>

int main() {
  using asking_star::soil::OperationKind;
  using asking_star::soil::SoilExecutionStatus;
  using asking_star::v55::AdapterMode;
  using asking_star::v55::ChamberExecutionRecord;
  using asking_star::v55::ChamberStarryOSDryRunBridge;

  ChamberStarryOSDryRunBridge bridge;

  const ChamberExecutionRecord dryrun{77, 55, AdapterMode::DryRun,
                                      "log-write starryos qemu-ready"};
  const auto dryrun_result = bridge.execute(dryrun);
  assert(dryrun_result.request.is_valid());
  assert(dryrun_result.request.operation_kind == OperationKind::LogWrite);
  assert(dryrun_result.result.ok());
  assert(dryrun_result.qemu_ready);
  assert(!dryrun_result.board_real_claim);
  assert(dryrun_result.result.message.find("dry-run") != std::string::npos);

  const ChamberExecutionRecord uart{78, 55, AdapterMode::DryRun,
                                    "uart starryos console"};
  const auto uart_result = bridge.execute(uart);
  assert(uart_result.request.operation_kind == OperationKind::UartWrite);
  assert(uart_result.result.ok());
  assert(uart_result.qemu_ready);

  const ChamberExecutionRecord board_real{79, 55, AdapterMode::BoardReal,
                                          "log-write board-real guarded"};
  const auto board_result = bridge.execute(board_real);
  assert(board_result.request.is_valid());
  assert(board_result.result.status == SoilExecutionStatus::UnsupportedOperation);
  assert(!board_result.qemu_ready);
  assert(!board_result.board_real_claim);

  return 0;
}
