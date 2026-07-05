#pragma once

#include <string>

namespace asking_star::core::responsibility {

struct ResponsibilityOwner {
  std::string id;
  std::string kind;

  [[nodiscard]] bool is_valid() const { return !id.empty() && !kind.empty(); }
};

}  // namespace asking_star::core::responsibility
