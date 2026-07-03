#pragma once

#include "core/charge/charge_token.h"

#include <string>
#include <vector>

namespace asking_star::core::gene {

enum class GeneKind {
  State,
  Ability,
  Rule,
  Skill,
  Reflex,
  Learned,
};

struct GeneCode {
  GeneId gene_id;
  GeneKind kind{GeneKind::State};
  std::string lineage_hash;
  std::string semantic_hash;
  std::string constraint_hash;
  std::string trajectory_hash;

  [[nodiscard]] bool is_valid() const {
    return gene_id.is_valid() && !lineage_hash.empty() &&
           !semantic_hash.empty() && !constraint_hash.empty() &&
           !trajectory_hash.empty();
  }

  [[nodiscard]] bool replaces_state_gene_fragment() const { return false; }
};

inline asking_star::core::charge::ChargeToken activate_gene_code(
    const GeneCode& code, asking_star::core::charge::ChargeKind kind,
    asking_star::core::charge::ProtocolBitMask protocols,
    asking_star::core::charge::ProtocolHashSet hashes,
    asking_star::core::charge::ProtocolWeightVector weights,
    double yin_charge, double yang_charge) {
  auto root = asking_star::core::charge::make_protocol_merkle_root(hashes);
  return asking_star::core::charge::ChargeToken{
      asking_star::core::charge::ChargeId{"charge-" + code.gene_id.value},
      kind,
      protocols,
      std::move(hashes),
      root,
      weights,
      {code.gene_id},
      std::nullopt,
      std::nullopt,
      std::nullopt,
      yin_charge,
      yang_charge,
      1.0,
      1.0,
      0,
      asking_star::core::charge::Layer::Runtime,
      asking_star::core::charge::Layer::Runtime,
      asking_star::core::charge::SoilVoltage{},
      asking_star::core::charge::GateBudget{10.0, 0.0},
      asking_star::RuntimeTemperature{}};
}

}  // namespace asking_star::core::gene
