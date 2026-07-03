#pragma once

#include "core/boot/boot_plan.h"
#include "core/charge/gate.h"
#include "core/charge/protocol_hash.h"

#include <cstddef>
#include <vector>

namespace asking_star::core::boot {

class BootGate {
 public:
  [[nodiscard]] asking_star::core::charge::ChargeToken make_token(
      const BootIntent& intent, const StarryOSArtifact& artifact) const {
    asking_star::core::charge::ChargeToken token;
    const std::vector<asking_star::core::charge::ChargeProtocol> protocols{
        asking_star::core::charge::ChargeProtocol::Force,
        asking_star::core::charge::ChargeProtocol::Law,
        asking_star::core::charge::ChargeProtocol::Wisdom};
    token.id.value = "charge-boot-" + intent.id;
    token.kind = asking_star::core::charge::ChargeKind::Light;
    for (const auto protocol : protocols) {
      token.protocols.add(protocol);
      token.protocol_hashes.hashes.push_back(
          asking_star::core::charge::make_protocol_hash(
              protocol, intent.id + ":" + artifact.kernel_image + ":" +
                            artifact.rootfs_image));
      token.weights.weights[static_cast<std::size_t>(protocol)] = 1.0;
    }
    token.protocol_root =
        asking_star::core::charge::make_protocol_merkle_root(
            token.protocol_hashes);
    token.from_layer = asking_star::core::charge::Layer::Runtime;
    token.to_layer = asking_star::core::charge::Layer::KernelSoil;
    token.energy = intent.allow_real_qemu ? 1.0 : 0.0;
    token.breath_intensity = 1.0;
    token.gate_budget.max_credit = 2.0;
    token.gate_budget.used_credit = intent.allow_real_qemu ? 0.5 : 2.0;
    token.source_voltage.pressure = 0.6;
    token.source_voltage.resistance = 0.2;
    token.source_voltage.risk_tolerance = 0.9;
    token.source_voltage.layer = asking_star::core::charge::Layer::KernelSoil;
    return token;
  }

  [[nodiscard]] asking_star::core::charge::GateDecisionTrace decide(
      const asking_star::core::charge::ChargeToken& token) const {
    auto decision = gate_.decide(token);
    return asking_star::core::charge::GateDecisionTrace{
        "gate-boot-" + token.id.value, token.id, decision};
  }

 private:
  asking_star::core::charge::Gate gate_;
};

}  // namespace asking_star::core::boot
