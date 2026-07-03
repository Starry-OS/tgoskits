#pragma once

#include "core/gene/gene_code.h"

#include <string>

namespace asking_star::core::gene {

struct CapabilityRequest {
  std::string capability;
  asking_star::core::charge::GateBudget budget;

  [[nodiscard]] bool is_valid() const {
    return !capability.empty() && budget.is_valid();
  }
};

struct YangDecodeResult {
  asking_star::core::charge::ChargeToken token;
  std::string projection;
  CapabilityRequest capability_request;

  [[nodiscard]] bool is_valid() const {
    return token.is_valid() && !projection.empty() &&
           capability_request.is_valid();
  }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }
};

class YangDecode {
 public:
  [[nodiscard]] YangDecodeResult decode(
      const GeneCode& code,
      const asking_star::RuntimeTemperature& temperature) const {
    asking_star::core::charge::ProtocolBitMask protocols;
    asking_star::core::charge::ProtocolWeightVector weights;
    asking_star::core::charge::ChargeKind kind{
        asking_star::core::charge::ChargeKind::Dual};
    std::vector<asking_star::core::charge::ProtocolHash> hashes;
    double yin_charge = 0.2;
    double yang_charge = 0.2;
    std::string projection = "runtime projection";

    if (temperature.absolute_zero) {
      protocols.add(asking_star::core::charge::ChargeProtocol::Law);
      weights.weights[1] = 1.0;
      kind = asking_star::core::charge::ChargeKind::Light;
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Law, code.semantic_hash));
      yin_charge = 1.0;
      projection = "light audit projection";
    } else if (temperature.unbounded || temperature.yang_temperature >
                                            temperature.yin_temperature) {
      protocols.add(asking_star::core::charge::ChargeProtocol::Force);
      protocols.add(asking_star::core::charge::ChargeProtocol::Hua);
      protocols.add(asking_star::core::charge::ChargeProtocol::Yun);
      weights.weights[0] = 1.0;
      weights.weights[3] = 1.0;
      weights.weights[4] = 1.0;
      kind = asking_star::core::charge::ChargeKind::Wave;
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Force, code.semantic_hash));
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Hua, code.lineage_hash));
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Yun,
          code.trajectory_hash));
      yang_charge = 1.0;
      projection = "execution projection";
    } else {
      protocols.add(asking_star::core::charge::ChargeProtocol::Law);
      protocols.add(asking_star::core::charge::ChargeProtocol::Meng);
      weights.weights[1] = 1.0;
      weights.weights[5] = 1.0;
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Law, code.constraint_hash));
      hashes.push_back(asking_star::core::charge::make_protocol_hash(
          asking_star::core::charge::ChargeProtocol::Meng,
          code.trajectory_hash));
      yin_charge = 1.0;
      projection = "risk audit projection";
    }

    asking_star::core::charge::ProtocolHashSet hash_set{hashes};
    auto token = asking_star::core::charge::ChargeToken{
        asking_star::core::charge::ChargeId{"decoded-" + code.gene_id.value},
        kind,
        protocols,
        hash_set,
        asking_star::core::charge::make_protocol_merkle_root(hash_set),
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
        asking_star::core::charge::Layer::Walker,
        asking_star::core::charge::SoilVoltage{},
        asking_star::core::charge::GateBudget{temperature.unbounded ? 50.0
                                                                    : 10.0,
                                              0.0},
        temperature};

    return YangDecodeResult{
        token, projection,
        CapabilityRequest{"projection-from-" + code.gene_id.value,
                          token.gate_budget}};
  }
};

}  // namespace asking_star::core::gene
