#include "asking_star/gcyy/projection_context.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool ProjectionContext::has_trace() const { return !trace_id.empty(); }

GcyyResult ProjectionContext::validate() const {
  if (context_id.empty()) {
    return GcyyResult::failure(GcyyStatus::InvalidArgument,
                               "projection context_id is required");
  }
  if (!has_trace()) {
    return GcyyResult::failure(GcyyStatus::MissingTraceId,
                               "projection trace_id is required");
  }
  return GcyyResult::success();
}

std::string ProjectionContext::debug_dump() const {
  std::ostringstream out;
  out << "ProjectionContext{id=" << context_id << ", trace=" << trace_id
      << ", mode=" << to_string(mode) << ", budget=" << budget_ref
      << ", rule=" << rule_version << "}";
  return out.str();
}

const char* to_string(ProjectionMode mode) {
  switch (mode) {
    case ProjectionMode::AskingStar:
      return "asking_star";
    case ProjectionMode::ShadowGuard:
      return "shadow_guard";
  }
  return "asking_star";
}

}  // namespace asking_star::gcyy

