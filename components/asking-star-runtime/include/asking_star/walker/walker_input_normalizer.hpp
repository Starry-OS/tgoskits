#pragma once

#include "asking_star/walker/walker_input.hpp"

namespace asking_star::walker {

// Normalizes external input without interpreting Gene or Charge semantics.
class WalkerInputNormalizer {
 public:
  [[nodiscard]] NormalizedWalkerInput normalize(const WalkerInput& input) const;
};

}  // namespace asking_star::walker
