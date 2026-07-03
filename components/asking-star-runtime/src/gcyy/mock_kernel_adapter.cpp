#include "asking_star/gcyy/mock_kernel_adapter.hpp"

namespace asking_star::gcyy {

KernelResult MockKernelAdapter::submit(const KernelRequest& request) const {
  if (!request.is_valid()) {
    return KernelResult{"result-invalid", request.request_id, request.trace_id,
                        GcyyStatus::AdapterError, "", "invalid_request", true};
  }
  return KernelResult{"result-" + request.request_id, request.request_id,
                      request.trace_id, GcyyStatus::Ok,
                      "mock-kernel://" + request.cell_id, "", true};
}

}  // namespace asking_star::gcyy

