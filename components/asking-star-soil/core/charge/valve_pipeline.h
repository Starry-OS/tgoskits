#pragma once

#include "core/charge/gate.h"
#include "core/charge/tree_output.h"
#include "core/charge/tree_stack.h"

#include <string>
#include <vector>

namespace asking_star::core::charge {

struct GateDecisionTrace {
  std::string id;
  ChargeId charge_id;
  GateDecision decision;

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && charge_id.is_valid() && decision.is_valid();
  }
};

struct SoilRequest {
  std::string id;
  ChargeFrame frame;
  GateDecisionTrace gate_trace;
  std::string operation;

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && frame.is_valid() && gate_trace.is_valid() &&
           !operation.empty();
  }

  [[nodiscard]] bool can_enter_kernel_soil() const {
    return gate_trace.decision.kind == GateDecisionKind::Pass ||
           gate_trace.decision.kind == GateDecisionKind::Reduce ||
           gate_trace.decision.kind == GateDecisionKind::Amplify;
  }
};

class ValvePipeline {
 public:
  [[nodiscard]] GateDecisionTrace decide(const ChargeFrame& frame) const {
    const auto decision = gate_.decide(frame.token);
    return GateDecisionTrace{
        "gate-" + stable_protocol_digest(frame.frame_id.value + ":" +
                                         frame.token.id.value),
        frame.token.id,
        decision};
  }

  [[nodiscard]] std::optional<SoilRequest> make_soil_request(
      const TreeOutput& output, const std::string& operation) const {
    if (!output.return_frame.has_value()) {
      return std::nullopt;
    }
    auto frame = *output.return_frame;
    auto gate_trace = decide(frame);
    frame.add_trace("gate:" + gate_trace.id + ":" + gate_trace.decision.reason);
    if (gate_trace.decision.kind == GateDecisionKind::Reject ||
        gate_trace.decision.kind == GateDecisionKind::Defer ||
        gate_trace.decision.kind == GateDecisionKind::Freeze ||
        gate_trace.decision.kind == GateDecisionKind::Seal) {
      return std::nullopt;
    }
    return SoilRequest{"soil-request-" + frame.frame_id.value, frame,
                       gate_trace, operation};
  }

  [[nodiscard]] bool replaces_gene_protocol() const { return false; }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }

 private:
  Gate gate_;
};

using ValveIngressStack = TreeStack;
using ValveEgressStack = TreeStack;

}  // namespace asking_star::core::charge
