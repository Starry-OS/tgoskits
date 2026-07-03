#pragma once

#include "core/charge/valve_pipeline.h"
#include "core/kernelsoil/execution_mode.h"

#include <string>

namespace asking_star::core::kernelsoil {

enum class SoilOperation {
  KernelTimeSleep,
  DriverSerialWrite,
  DriverRknpuSubmit,
  DriverRknpuWaitIrq,
  DriverDmaAlloc,
  KernelIoctl,
};

struct SoilRequest {
  std::string id;
  SoilOperation operation{SoilOperation::KernelTimeSleep};
  asking_star::core::charge::GateDecisionTrace gate_trace;
  std::string payload;
  std::string route_id;
  bool dry_run{true};
  ExecutionMode mode{ExecutionMode::Mock};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && gate_trace.is_valid() && !payload.empty();
  }

  [[nodiscard]] std::string trace_id() const {
    if (!route_id.empty()) {
      return route_id + ":" + id;
    }
    return id;
  }

  [[nodiscard]] bool can_dispatch() const {
    return gate_trace.decision.kind ==
               asking_star::core::charge::GateDecisionKind::Pass ||
           gate_trace.decision.kind ==
               asking_star::core::charge::GateDecisionKind::Reduce ||
           gate_trace.decision.kind ==
               asking_star::core::charge::GateDecisionKind::Amplify;
  }
};

inline const char* to_string(SoilOperation operation) {
  switch (operation) {
    case SoilOperation::KernelTimeSleep:
      return "Kernel.Time.Sleep";
    case SoilOperation::DriverSerialWrite:
      return "Driver.Serial.Write";
    case SoilOperation::DriverRknpuSubmit:
      return "Driver.Rknpu.Submit";
    case SoilOperation::DriverRknpuWaitIrq:
      return "Driver.Rknpu.WaitIrq";
    case SoilOperation::DriverDmaAlloc:
      return "Driver.Dma.Alloc";
    case SoilOperation::KernelIoctl:
      return "Kernel.Ioctl";
  }
  return "Kernel.Time.Sleep";
}

}  // namespace asking_star::core::kernelsoil
