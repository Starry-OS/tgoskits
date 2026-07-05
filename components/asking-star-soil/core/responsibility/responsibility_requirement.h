#pragma once

#include <string>

namespace asking_star::core::responsibility {

struct ResponsibilityRequirement {
  std::string required_capability;
  std::string reason;

  [[nodiscard]] bool is_valid() const {
    return !required_capability.empty() && !reason.empty();
  }
};

}  // namespace asking_star::core::responsibility
