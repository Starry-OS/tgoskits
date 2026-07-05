#pragma once

#include "core/dualchain/dual_link_hash.h"
#include "core/responsibility/responsibility_trace_id.h"
#include "core/statechain/state_gene_id.h"

#include <string>
#include <vector>

namespace asking_star::core::dualchain {

struct ActiveDualNode {
  asking_star::core::statechain::StateGeneId state_id;
  asking_star::core::responsibility::ResponsibilityTraceId trace_id;
  DualLinkHash link_hash;
  float score{0.0F};
  std::string reason;

  [[nodiscard]] bool is_valid() const {
    return state_id.is_valid() && trace_id.is_valid() && link_hash.is_valid() &&
           !reason.empty();
  }
};

struct ActiveDualSubgraph {
  std::string window_id;
  std::vector<ActiveDualNode> nodes;

  [[nodiscard]] bool is_valid() const {
    if (window_id.empty() || nodes.empty()) {
      return false;
    }
    for (const auto& node : nodes) {
      if (!node.is_valid()) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] bool stores_authoritative_state() const {
    return false;
  }
};

}  // namespace asking_star::core::dualchain
