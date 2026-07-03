#pragma once

#include "common_types.h"
#include "core/responsibility/responsibility_trace_id.h"
#include "core/statechain/state_gene_id.h"

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace asking_star::core::event {

enum class DualChainEventKind {
  StatePending,
  StateGenerated,
  StateRejected,
  ResponsibilityScheduled,
  ResponsibilityFailed,
  ResponsibilityFeedbackReturned,
  StateSealed,
  StatePromoted,
};

struct DualChainEvent {
  std::uint64_t sequence{0};
  DualChainEventKind kind{DualChainEventKind::StatePending};
  std::optional<asking_star::core::statechain::StateGeneId> state_id;
  std::optional<asking_star::core::responsibility::ResponsibilityTraceId>
      trace_id;
  std::string reason;
  asking_star::Timestamp occurred_at{asking_star::now()};

  [[nodiscard]] bool is_valid() const {
    return sequence > 0 && !reason.empty() &&
           (state_id.has_value() || trace_id.has_value());
  }
};

class DualChainEventStore {
 public:
  DualChainEvent append(DualChainEventKind kind,
                        std::optional<asking_star::core::statechain::StateGeneId>
                            state_id,
                        std::optional<
                            asking_star::core::responsibility::ResponsibilityTraceId>
                            trace_id,
                        std::string reason) {
    if (reason.empty() || (!state_id.has_value() && !trace_id.has_value())) {
      throw std::invalid_argument("invalid dual-chain event");
    }
    DualChainEvent event{next_sequence_++, kind, std::move(state_id),
                         std::move(trace_id), std::move(reason)};
    events_.push_back(event);
    return event;
  }

  [[nodiscard]] std::vector<DualChainEvent> replay() const {
    return events_;
  }

 private:
  std::uint64_t next_sequence_{1};
  std::vector<DualChainEvent> events_;
};

}  // namespace asking_star::core::event
