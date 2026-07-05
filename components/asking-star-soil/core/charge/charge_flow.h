#pragma once

#include "core/charge/charge_token.h"

#include <string>
#include <vector>

namespace asking_star::core::charge {

struct ChargeFlow {
  std::string id;
  std::vector<ChargeToken> tokens;

  [[nodiscard]] bool is_valid() const {
    if (id.empty() || tokens.empty()) {
      return false;
    }
    for (const auto& token : tokens) {
      if (!token.is_valid()) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] double total_yin_charge() const {
    double total = 0.0;
    for (const auto& token : tokens) {
      total += token.yin_charge + token.weights.yin_bias();
    }
    return total;
  }

  [[nodiscard]] double total_yang_charge() const {
    double total = 0.0;
    for (const auto& token : tokens) {
      total += token.yang_charge + token.weights.yang_bias();
    }
    return total;
  }

  [[nodiscard]] bool writes_genebank() const { return false; }
};

}  // namespace asking_star::core::charge
