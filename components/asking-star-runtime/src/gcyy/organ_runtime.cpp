#include "asking_star/gcyy/organ_runtime.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool OrganResult::ok() const { return status == GcyyStatus::Ok; }

std::string OrganResult::debug_dump() const {
  std::ostringstream out;
  out << "OrganResult{organ=" << organ_id << ", cell=" << cell_id
      << ", trace=" << trace_id << ", status=" << to_string(status)
      << ", message=" << message << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

