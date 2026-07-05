#pragma once

#include "core/charge/protocol_hash.h"

#include <cstdint>
#include <string>

namespace asking_star::core::charge {

struct ChargeId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};

struct FrameId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};

struct RouteId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};

inline ChargeId make_charge_id(const ProtocolMerkleRoot& root,
                               const std::string& semantic_key) {
  return ChargeId{"charge-" + stable_protocol_digest(root.digest + ":" +
                                                     semantic_key)};
}

inline FrameId make_frame_id(const ChargeId& charge_id,
                             std::uint64_t sequence) {
  return FrameId{"frame-" + std::to_string(sequence) + "-" +
                 stable_protocol_digest(charge_id.value)};
}

inline RouteId make_route_id(const FrameId& frame_id,
                             const std::string& route_seed) {
  return RouteId{"route-" + stable_protocol_digest(frame_id.value + ":" +
                                                   route_seed)};
}

}  // namespace asking_star::core::charge
