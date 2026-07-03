#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <string>

namespace asking_star::gcyy {

enum class ProjectionMode {
  AskingStar,
  ShadowGuard,
};

// ProjectionContext carries policy references for GCYY projection.
struct ProjectionContext {
  std::string context_id;
  std::string trace_id;
  ProjectionMode mode{ProjectionMode::AskingStar};
  std::string budget_ref;
  std::string rule_version;
  bool trace_enabled{true};

  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] GcyyResult validate() const;
  [[nodiscard]] std::string debug_dump() const;
};

[[nodiscard]] const char* to_string(ProjectionMode mode);

}  // namespace asking_star::gcyy

