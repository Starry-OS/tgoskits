#pragma once

#include "common_types.h"
#include "core/charge/charge_id.h"
#include "core/charge/charge_protocol.h"
#include "core/charge/protocol_hash.h"
#include "core/charge/soil_voltage.h"
#include "core/dualchain/dual_link_hash.h"
#include "core/responsibility/responsibility_trace_id.h"
#include "core/statechain/state_gene_id.h"

#include <optional>
#include <string>
#include <vector>

namespace asking_star::core::gene {
struct GeneId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};
}  // namespace asking_star::core::gene

namespace asking_star::core::charge {

struct ChargeToken {
  ChargeId id;
  ChargeKind kind{ChargeKind::Dual};
  ProtocolBitMask protocols;
  ProtocolHashSet protocol_hashes;
  ProtocolMerkleRoot protocol_root;
  ProtocolWeightVector weights;
  std::vector<asking_star::core::gene::GeneId> gene_refs;
  std::optional<asking_star::core::statechain::StateGeneId> state_id;
  std::optional<asking_star::core::responsibility::ResponsibilityTraceId>
      trace_id;
  std::optional<asking_star::core::dualchain::DualLinkHash> anchor;
  double yin_charge{0.0};
  double yang_charge{0.0};
  double energy{0.0};
  double breath_intensity{0.0};
  int compression_level{0};
  Layer from_layer{Layer::Walker};
  Layer to_layer{Layer::Runtime};
  SoilVoltage source_voltage;
  GateBudget gate_budget;
  asking_star::RuntimeTemperature temperature;
  asking_star::Timestamp created_at{asking_star::now()};

  [[nodiscard]] bool is_valid() const {
    return id.is_valid() && protocols.is_valid() && protocol_hashes.is_valid() &&
           protocol_root.is_valid() && weights.is_valid() &&
           yin_charge >= 0.0 && yang_charge >= 0.0 && energy >= 0.0 &&
           breath_intensity >= 0.0 && compression_level >= 0 &&
           source_voltage.is_valid() && gate_budget.is_valid() &&
           temperature.is_valid();
  }

  [[nodiscard]] bool references_dual_anchor() const {
    return state_id.has_value() && trace_id.has_value() && anchor.has_value() &&
           state_id->is_valid() && trace_id->is_valid() && anchor->is_valid();
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool is_yin_biased() const {
    return yin_charge + weights.yin_bias() > yang_charge + weights.yang_bias();
  }

  [[nodiscard]] bool is_yang_biased() const {
    return yang_charge + weights.yang_bias() > yin_charge + weights.yin_bias();
  }
};

}  // namespace asking_star::core::charge
