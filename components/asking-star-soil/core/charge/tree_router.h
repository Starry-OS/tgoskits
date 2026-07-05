#pragma once

#include "common_types.h"
#include "core/charge/tree_port.h"

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

namespace asking_star::core::charge {

struct TreeRouteDecision {
  std::string selected_tree_id;
  double score{0.0};
  std::string reason;
  std::vector<std::string> route_trace;

  [[nodiscard]] bool is_valid() const {
    return !selected_tree_id.empty() && !reason.empty();
  }
};

class TreeRouter {
 public:
  [[nodiscard]] std::optional<TreeRouteDecision> route(
      const ChargeFrame& frame,
      const std::vector<TreePortDescriptor>& ports,
      asking_star::RuntimeMode mode = asking_star::RuntimeMode::AskingStar)
      const {
    std::optional<TreeRouteDecision> best;
    for (const auto& port : ports) {
      if (!port.is_valid()) {
        continue;
      }
      const auto score = score_port(frame, port, mode);
      if (!best.has_value() || score > best->score) {
        auto trace = frame.route_trace;
        trace.push_back("router:selected:" + port.tree_id);
        best = TreeRouteDecision{port.tree_id, score, explain(score, port),
                                 trace};
      }
    }
    return best;
  }

  [[nodiscard]] bool replaces_scheduler() const { return false; }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool bypasses_gate() const { return false; }

 private:
  [[nodiscard]] static bool contains_layer(const TreePortDescriptor& port,
                                           Layer layer) {
    return std::find(port.accepted_layers.begin(), port.accepted_layers.end(),
                     layer) != port.accepted_layers.end();
  }

  [[nodiscard]] static bool contains_protocol(const TreePortDescriptor& port,
                                              ChargeProtocol protocol) {
    return std::find(port.accepted_protocols.begin(),
                     port.accepted_protocols.end(),
                     protocol) != port.accepted_protocols.end();
  }

  [[nodiscard]] static double score_port(
      const ChargeFrame& frame, const TreePortDescriptor& port,
      asking_star::RuntimeMode mode) {
    double score = 0.0;
    for (const auto protocol : {ChargeProtocol::Force, ChargeProtocol::Law,
                                ChargeProtocol::Wisdom, ChargeProtocol::Hua,
                                ChargeProtocol::Yun, ChargeProtocol::Meng}) {
      if (frame.token.protocols.contains(protocol) &&
          contains_protocol(port, protocol)) {
        score += 2.0;
      }
    }
    for (const auto& hint : frame.capability_hints) {
      if (std::find(port.accepted_capabilities.begin(),
                    port.accepted_capabilities.end(),
                    hint) != port.accepted_capabilities.end()) {
        score += 3.0;
      }
    }
    if (contains_layer(port, frame.token.to_layer)) {
      score += 1.0;
    }
    if (port.shadow_guard || mode == asking_star::RuntimeMode::ShadowGuard) {
      score += frame.risk_score >= 0.7 ? 4.0 : -1.0;
    } else {
      score -= frame.risk_score;
    }
    return score;
  }

  [[nodiscard]] static std::string explain(double score,
                                           const TreePortDescriptor& port) {
    return "affinity score " + std::to_string(score) + " selected " +
           port.tree_id;
  }
};

}  // namespace asking_star::core::charge
