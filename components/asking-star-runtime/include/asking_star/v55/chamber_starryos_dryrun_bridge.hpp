#pragma once

#include "asking_star/soil/adapters/starryos_adapter.hpp"
#include "asking_star/soil/kernel_request.hpp"
#include "asking_star/v55/chamber_pouch.hpp"

#include <string>

namespace asking_star::v55 {

struct StarryOSDryRunBridgeRecord {
  ChamberExecutionRecord execution;
  asking_star::soil::KernelRequest request;
  asking_star::soil::KernelResult result;
  bool qemu_ready{false};
  bool board_real_claim{false};
};

[[nodiscard]] inline asking_star::soil::OperationKind
operation_from_chamber_payload(const std::string& payload) {
  if (payload.find("uart") != std::string::npos) {
    return asking_star::soil::OperationKind::UartWrite;
  }
  if (payload.find("ioctl") != std::string::npos) {
    return asking_star::soil::OperationKind::DeviceIoctl;
  }
  return asking_star::soil::OperationKind::LogWrite;
}

[[nodiscard]] inline asking_star::soil::adapters::StarryOSAdapterMode
starryos_mode_from_chamber(AdapterMode mode) {
  if (mode == AdapterMode::HostMock || mode == AdapterMode::Host) {
    return asking_star::soil::adapters::StarryOSAdapterMode::HostMock;
  }
  if (mode == AdapterMode::BoardReal) {
    return asking_star::soil::adapters::StarryOSAdapterMode::BoardReal;
  }
  return asking_star::soil::adapters::StarryOSAdapterMode::DryRun;
}

[[nodiscard]] inline asking_star::soil::KernelRequest
make_starryos_kernel_request(const ChamberExecutionRecord& execution) {
  asking_star::soil::KernelRequest request;
  request.request_id.value =
      "v55-starryos-" + std::to_string(execution.execution_id);
  request.trace_id = "v55-chamber-" + std::to_string(execution.placement_id);
  request.cell_id = std::to_string(execution.placement_id);
  request.origin_gene_id = "v55-chamber-gene";
  request.origin_charge_id =
      "v55-chamber-charge-" + std::to_string(execution.execution_id);
  request.operation_kind = operation_from_chamber_payload(execution.request_payload);
  request.target_kind = "starryos.console";
  request.payload = execution.request_payload;
  request.expected_result_kind = "DigitalSetFragment";
  request.timeout_budget = 1000000;
  request.priority = 1;
  return request;
}

class ChamberStarryOSDryRunBridge {
 public:
  [[nodiscard]] StarryOSDryRunBridgeRecord execute(
      const ChamberExecutionRecord& execution) const {
    StarryOSDryRunBridgeRecord bridge;
    bridge.execution = execution;
    bridge.request = make_starryos_kernel_request(execution);

    const bool enabled = execution.adapter_mode == AdapterMode::BoardReal;
    asking_star::soil::adapters::StarryOSAdapter adapter{
        {enabled, starryos_mode_from_chamber(execution.adapter_mode)}};
    bridge.result = adapter.execute(bridge.request);
    bridge.qemu_ready = bridge.request.is_valid() && bridge.result.ok() &&
                        execution.adapter_mode != AdapterMode::BoardReal;
    bridge.board_real_claim = false;
    return bridge;
  }
};

}  // namespace asking_star::v55
