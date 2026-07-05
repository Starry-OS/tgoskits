#include "asking_star/gcyy/kernel_result.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool KernelResult::ok() const { return status == GcyyStatus::Ok; }

bool KernelResult::is_valid() const {
  return !result_id.empty() && !request_id.empty() && !trace_id.empty() &&
         dry_run && (ok() || !error_code.empty());
}

std::string KernelResult::debug_dump() const {
  std::ostringstream out;
  out << "KernelResult{id=" << result_id << ", request=" << request_id
      << ", trace=" << trace_id << ", status=" << to_string(status)
      << ", dry_run=" << (dry_run ? "true" : "false") << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

