#pragma once

#include "core/dualchain/dual_gene_anchor.h"
#include "core/dualchain/dual_replay.h"
#include "core/event/dual_chain_event.h"
#include "core/genebank/gene_bank.h"

#include <string>
#include <vector>

namespace asking_star::core::dualchain {

enum class DualConsistencyStatus {
  Ok,
  MissingState,
  MissingTrace,
  MissingDualLink,
  HashMismatch,
  EventOrderBroken,
};

struct DualConsistencyReport {
  DualConsistencyStatus status{DualConsistencyStatus::Ok};
  std::string reason{"ok"};

  [[nodiscard]] bool ok() const {
    return status == DualConsistencyStatus::Ok;
  }
};

class DualConsistencyChecker {
 public:
  [[nodiscard]] DualConsistencyReport check_anchor(
      const asking_star::core::genebank::GeneBank& bank,
      const DualGeneAnchor& anchor) const {
    if (!bank.get_state(anchor.state_gene_id).has_value()) {
      return {DualConsistencyStatus::MissingState, "missing state fragment"};
    }
    if (!bank.get_trace(anchor.trace_id).has_value()) {
      return {DualConsistencyStatus::MissingTrace,
              "missing responsibility trace"};
    }

    const auto expected_hash = make_dual_link_hash(
        anchor.state_gene_id.value, anchor.trace_id.value, anchor.reason,
        anchor.event_id);
    if (!(expected_hash == anchor.link_hash)) {
      return {DualConsistencyStatus::HashMismatch, "dual link hash mismatch"};
    }

    if (!bank.replay_dual_link(anchor.link_hash).has_value()) {
      return {DualConsistencyStatus::MissingDualLink, "missing dual link"};
    }

    return {};
  }

  [[nodiscard]] DualConsistencyReport check_event_order(
      const std::vector<asking_star::core::event::DualChainEvent>& events) const {
    std::uint64_t previous_sequence = 0;
    for (const auto& event : events) {
      if (event.sequence <= previous_sequence) {
        return {DualConsistencyStatus::EventOrderBroken,
                "dual-chain event order is broken"};
      }
      previous_sequence = event.sequence;
    }
    return {};
  }

  [[nodiscard]] DualConsistencyReport check_replay_view(
      const DualReplayView& view) const {
    return check_event_order(view.events);
  }
};

}  // namespace asking_star::core::dualchain
