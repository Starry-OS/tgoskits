#pragma once

#include "core/dualchain/dual_link_hash.h"
#include "core/responsibility/responsibility_trace_id.h"
#include "core/statechain/state_gene_id.h"

#include <string>

namespace asking_star::core::dualchain {

struct DualGeneAnchor {
  asking_star::core::statechain::StateGeneId state_gene_id;
  asking_star::core::responsibility::ResponsibilityTraceId trace_id;
  DualLinkHash link_hash;
  std::string reason;
  std::string event_id;

  [[nodiscard]] bool is_valid() const {
    return state_gene_id.is_valid() && trace_id.is_valid() &&
           link_hash.is_valid() && !reason.empty() && !event_id.empty();
  }
};

inline DualGeneAnchor make_dual_gene_anchor(
    asking_star::core::statechain::StateGeneId state_gene_id,
    asking_star::core::responsibility::ResponsibilityTraceId trace_id,
    std::string reason, std::string event_id) {
  auto link_hash = make_dual_link_hash(state_gene_id.value, trace_id.value,
                                       reason, event_id);
  return DualGeneAnchor{std::move(state_gene_id), std::move(trace_id),
                        std::move(link_hash), std::move(reason),
                        std::move(event_id)};
}

}  // namespace asking_star::core::dualchain
