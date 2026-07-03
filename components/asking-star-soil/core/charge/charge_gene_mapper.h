#pragma once

#include "core/charge/charge_frame.h"
#include "core/charge/charge_payload.h"
#include "core/gene/gene_code.h"

#include <string>

namespace asking_star::core::charge {

struct ChargeGeneCandidate {
  asking_star::core::gene::GeneCode code;
  ChargeId source_charge_id;
  FrameId source_frame_id;
  bool requires_sheng_admission{true};

  [[nodiscard]] bool is_valid() const {
    return code.is_valid() && source_charge_id.is_valid() &&
           source_frame_id.is_valid();
  }

  [[nodiscard]] bool writes_genebank() const { return false; }
};

class ChargeGeneMapper {
 public:
  [[nodiscard]] ChargeGeneCandidate map_to_candidate(
      const ChargeFrame& frame, const ChargePayload& payload) const {
    const auto route_digest = route_hash(frame);
    auto candidate_id = asking_star::core::gene::GeneId{
        "gene-candidate-" + stable_protocol_digest(frame.token.id.value + ":" +
                                                   payload.semantic_key + ":" +
                                                   route_digest)};
    return ChargeGeneCandidate{
        asking_star::core::gene::GeneCode{
            candidate_id,
            asking_star::core::gene::GeneKind::Learned,
            stable_protocol_digest(frame.token.protocol_root.digest + ":" +
                                   frame.token.id.value),
            stable_protocol_digest(payload.semantic_key + ":" + payload.body),
            stable_protocol_digest(std::to_string(frame.token.protocols.value()) +
                                   ":" + frame.token.protocol_root.digest),
            stable_protocol_digest(route_digest + ":" +
                                   std::to_string(frame.token.energy))},
        frame.token.id,
        frame.frame_id,
        true};
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool admits_with_sheng() const { return false; }

 private:
  [[nodiscard]] static std::string route_hash(const ChargeFrame& frame) {
    std::string joined = frame.route_id.value + ":" + frame.current_tree;
    for (const auto& entry : frame.route_trace) {
      joined += ":" + entry;
    }
    return stable_protocol_digest(joined);
  }
};

}  // namespace asking_star::core::charge
