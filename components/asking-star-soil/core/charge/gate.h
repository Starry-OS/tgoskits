#pragma once

#include "core/charge/charge_token.h"

#include <string>

namespace asking_star::core::charge {

enum class GateDecisionKind {
  Pass,
  Reduce,
  Amplify,
  Freeze,
  Reject,
  Defer,
  Seal,
};

struct GateDecision {
  GateDecisionKind kind{GateDecisionKind::Reject};
  double output_energy{0.0};
  double output_breath_intensity{0.0};
  std::string reason;

  [[nodiscard]] bool is_valid() const { return !reason.empty(); }
};

class Gate {
 public:
  [[nodiscard]] GateDecision decide(const ChargeToken& token) const {
    if (!token.is_valid()) {
      return {GateDecisionKind::Reject, 0.0, 0.0, "invalid charge token"};
    }
    if (token.temperature.absolute_zero) {
      if (token.kind == ChargeKind::Light &&
          token.protocols.contains(ChargeProtocol::Law)) {
        return {GateDecisionKind::Freeze, 0.0, 0.1,
                "absolute zero allows only light audit charge"};
      }
      return {GateDecisionKind::Reject, 0.0, 0.0,
              "absolute zero rejects state generation"};
    }
    if (token.temperature.unbounded && token.gate_budget.max_credit <= 0.0) {
      return {GateDecisionKind::Reject, 0.0, 0.0,
              "unbounded temperature requires gate budget"};
    }
    if (token.gate_budget.remaining() <= 0.0) {
      return {GateDecisionKind::Defer, 0.0, 0.0, "gate budget exhausted"};
    }
    if (token.source_voltage.resistance > token.source_voltage.risk_tolerance) {
      return {GateDecisionKind::Reduce, token.energy * 0.5,
              token.breath_intensity * 0.5, "soil voltage reduced charge"};
    }
    if (token.source_voltage.pressure > token.source_voltage.resistance &&
        token.gate_budget.remaining() >= token.energy) {
      return {GateDecisionKind::Amplify, token.energy * 1.25,
              token.breath_intensity * 1.25, "soil voltage amplified charge"};
    }
    return {GateDecisionKind::Pass, token.energy, token.breath_intensity,
            "charge passed gate"};
  }

  [[nodiscard]] bool replaces_gene_protocol() const { return false; }
};

}  // namespace asking_star::core::charge
