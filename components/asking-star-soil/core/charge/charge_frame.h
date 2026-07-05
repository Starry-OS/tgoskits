#pragma once

#include "core/charge/charge_id.h"
#include "core/charge/charge_token.h"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::core::charge {

struct ChargeFrame {
  FrameId frame_id;
  std::uint64_t sequence{0};
  ChargeToken token;
  RouteId route_id;
  std::string current_tree;
  std::vector<std::string> route_trace;
  std::vector<std::string> capability_hints;
  double risk_score{0.0};

  [[nodiscard]] bool is_valid() const {
    return frame_id.is_valid() && sequence > 0 && token.is_valid() &&
           route_id.is_valid() && risk_score >= 0.0;
  }

  void add_trace(std::string entry) {
    if (!entry.empty()) {
      route_trace.push_back(std::move(entry));
    }
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }
};

inline ChargeFrame make_charge_frame(ChargeToken token, std::uint64_t sequence,
                                     const std::string& route_seed = "road") {
  auto frame_id = make_frame_id(token.id, sequence);
  auto route_id = make_route_id(frame_id, route_seed);
  ChargeFrame frame{frame_id, sequence, std::move(token), route_id};
  frame.add_trace("frame:" + frame.frame_id.value);
  frame.add_trace("route:" + frame.route_id.value);
  return frame;
}

}  // namespace asking_star::core::charge
