#include "asking_star/gcyy/gcyy_result.hpp"

#include <sstream>
#include <utility>

namespace asking_star::gcyy {

bool GcyyResult::ok() const { return status == GcyyStatus::Ok; }

std::string GcyyResult::debug_dump() const {
  std::ostringstream out;
  out << "GcyyResult{status=" << to_string(status) << ", message=" << message
      << "}";
  return out.str();
}

GcyyResult GcyyResult::success() { return {}; }

GcyyResult GcyyResult::failure(GcyyStatus status, std::string message) {
  return GcyyResult{status, std::move(message)};
}

const char* to_string(GcyyStatus status) {
  switch (status) {
    case GcyyStatus::Ok:
      return "ok";
    case GcyyStatus::InvalidArgument:
      return "invalid_argument";
    case GcyyStatus::MissingTraceId:
      return "missing_trace_id";
    case GcyyStatus::MissingPayload:
      return "missing_payload";
    case GcyyStatus::MissingGene:
      return "missing_gene";
    case GcyyStatus::InvalidState:
      return "invalid_state";
    case GcyyStatus::NotFound:
      return "not_found";
    case GcyyStatus::Denied:
      return "denied";
    case GcyyStatus::BudgetExhausted:
      return "budget_exhausted";
    case GcyyStatus::AdapterError:
      return "adapter_error";
  }
  return "invalid_state";
}

}  // namespace asking_star::gcyy
