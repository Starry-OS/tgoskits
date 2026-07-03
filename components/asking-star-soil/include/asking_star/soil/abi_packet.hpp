#pragma once

#include "asking_star/soil/kernel_request.hpp"
#include "asking_star/soil/memory_buffer_view.hpp"
#include "asking_star/soil/syscall_plan.hpp"

namespace asking_star::soil {

struct AbiPacket {
  SoilRequestId request_id;
  std::string trace_id;
  OperationKind operation_kind{OperationKind::Unknown};
  std::string target_kind;
  MemoryBufferView payload;
  SyscallPlan plan;

  [[nodiscard]] bool is_valid() const {
    return request_id.is_valid() && !trace_id.empty() &&
           operation_kind != OperationKind::Unknown && payload.is_valid() &&
           plan.is_valid();
  }
};

[[nodiscard]] AbiPacket make_abi_packet(const KernelRequest& request);

}  // namespace asking_star::soil

