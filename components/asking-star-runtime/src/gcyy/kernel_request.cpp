#include "asking_star/gcyy/kernel_request.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool KernelRequest::is_valid() const {
  return !request_id.empty() && !cell_id.empty() && !trace_id.empty() &&
         dry_run;
}

std::string KernelRequest::debug_dump() const {
  std::ostringstream out;
  out << "KernelRequest{id=" << request_id << ", cell=" << cell_id
      << ", trace=" << trace_id << ", op=" << operation_kind
      << ", dry_run=" << (dry_run ? "true" : "false") << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

