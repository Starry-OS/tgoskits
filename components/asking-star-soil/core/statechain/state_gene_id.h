#pragma once

#include "core/dualchain/dual_link_hash.h"

#include <string>
#include <string_view>

namespace asking_star::core::statechain {

struct StateGeneId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }

  friend bool operator==(const StateGeneId& lhs, const StateGeneId& rhs) {
    return lhs.value == rhs.value;
  }
};

inline StateGeneId make_state_gene_id(std::string_view parent,
                                      std::string_view xing,
                                      std::string_view ming,
                                      std::string_view sheng,
                                      std::string_view influence,
                                      std::string_view payload,
                                      std::string_view salt) {
  asking_star::core::dualchain::StableHashInput input;
  input.add("state-gene")
      .add(parent)
      .add(xing)
      .add(ming)
      .add(sheng)
      .add(influence)
      .add(payload)
      .add(salt);
  return StateGeneId{
      asking_star::core::dualchain::make_hash_digest(input).value};
}

}  // namespace asking_star::core::statechain
