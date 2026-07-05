#pragma once

#include "core/dualchain/dual_link_hash.h"

#include <string>
#include <string_view>

namespace asking_star::core::responsibility {

struct ResponsibilityTraceId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }

  friend bool operator==(const ResponsibilityTraceId& lhs,
                         const ResponsibilityTraceId& rhs) {
    return lhs.value == rhs.value;
  }
};

inline ResponsibilityTraceId make_responsibility_trace_id(
    std::string_view scheduler_pulse, std::string_view owner,
    std::string_view action, std::string_view requirement,
    std::string_view salt) {
  asking_star::core::dualchain::StableHashInput input;
  input.add("responsibility-trace")
      .add(scheduler_pulse)
      .add(owner)
      .add(action)
      .add(requirement)
      .add(salt);
  return ResponsibilityTraceId{
      asking_star::core::dualchain::make_hash_digest(input).value};
}

}  // namespace asking_star::core::responsibility
