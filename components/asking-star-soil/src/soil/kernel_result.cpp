#include "asking_star/soil/kernel_result.hpp"

#include <sstream>

namespace asking_star::soil {

bool KernelResult::ok() const { return is_success(status); }

bool KernelResult::is_valid() const {
  return request_id.is_valid() && !trace_id.empty() &&
         (ok() || (!error_code.empty() && !message.empty()));
}

KernelError KernelResult::error() const {
  return KernelError{status, error_code, message};
}

std::string KernelResult::debug_dump() const {
  std::ostringstream out;
  out << "KernelResult{request=" << request_id.value << ", trace=" << trace_id
      << ", status=" << to_string(status) << ", error=" << error_code
      << ", latency_ns=" << latency_ns << "}";
  return out.str();
}

}  // namespace asking_star::soil

