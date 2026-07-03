#pragma once

#include <string>

namespace asking_star::compat {

struct CompatibilityView {
  std::string legacy_type;
  std::string v5_type;
  std::string trace_id;
  bool runtime_core_participant{false};

  [[nodiscard]] bool is_valid() const {
    return !legacy_type.empty() && !v5_type.empty() && !trace_id.empty();
  }
};

}  // namespace asking_star::compat

