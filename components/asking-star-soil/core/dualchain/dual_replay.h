#pragma once

#include "core/dualchain/dual_link_hash.h"
#include "core/event/dual_chain_event.h"
#include "core/genebank/gene_bank.h"

#include <vector>

namespace asking_star::core::dualchain {

struct DualReplayView {
  asking_star::core::genebank::DualReplayRecord record;
  std::vector<asking_star::core::event::DualChainEvent> events;
};

class DualReplay {
 public:
  DualReplay(const asking_star::core::genebank::GeneBank& bank,
             const asking_star::core::event::DualChainEventStore& events)
      : bank_(bank), events_(events) {}

  [[nodiscard]] std::optional<DualReplayView> load(
      const DualLinkHash& hash) const {
    auto record = bank_.replay_dual_link(hash);
    if (!record.has_value()) {
      return std::nullopt;
    }

    std::vector<asking_star::core::event::DualChainEvent> matching_events;
    for (const auto& event : events_.replay()) {
      const bool same_state =
          event.state_id.has_value() &&
          event.state_id->value == record->state.id.value;
      const bool same_trace =
          event.trace_id.has_value() &&
          event.trace_id->value == record->trace.id.value;
      if (same_state || same_trace) {
        matching_events.push_back(event);
      }
    }

    return DualReplayView{*record, std::move(matching_events)};
  }

 private:
  const asking_star::core::genebank::GeneBank& bank_;
  const asking_star::core::event::DualChainEventStore& events_;
};

}  // namespace asking_star::core::dualchain
