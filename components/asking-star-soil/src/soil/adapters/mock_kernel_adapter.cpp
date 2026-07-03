#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"

namespace asking_star::soil::adapters {

KernelResult MockKernelAdapter::execute(const KernelRequest& request) const {
  if (request.request_id.is_valid() && !request.trace_id.empty() &&
      request.operation_kind == OperationKind::Unknown) {
    return KernelResult{request.request_id,
                        request.trace_id,
                        SoilExecutionStatus::UnsupportedOperation,
                        "UnsupportedOperation",
                        "",
                        0,
                        "unsupported operation"};
  }
  if (!request.is_valid()) {
    return KernelResult{request.request_id,
                        request.trace_id,
                        SoilExecutionStatus::InvalidRequest,
                        "InvalidRequest",
                        "",
                        0,
                        "invalid soil request"};
  }
  return KernelResult{request.request_id,
                      request.trace_id,
                      SoilExecutionStatus::Ok,
                      "",
                      "mock-result:" + request.payload,
                      1,
                      "mock adapter executed"};
}

}  // namespace asking_star::soil::adapters
