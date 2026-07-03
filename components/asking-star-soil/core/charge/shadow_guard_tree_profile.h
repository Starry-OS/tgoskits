#pragma once

#include "core/charge/tree_output.h"
#include "core/charge/tree_port.h"

namespace asking_star::core::charge {

struct ShadowGuardProjection {
  std::string id;
  std::string kind;
  bool audit_light{true};
  bool mutates_primary_state{false};
  bool executes_kernel_soil{false};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && !kind.empty() && audit_light;
  }
};

class ShadowGuardTreeProfile {
 public:
  [[nodiscard]] TreePortDescriptor descriptor() const {
    return TreePortDescriptor{
        "shadow-guard-tree",
        {ChargeProtocol::Law, ChargeProtocol::Wisdom, ChargeProtocol::Meng},
        {"risk.audit", "shadow.observe"},
        {Layer::Runtime},
        32,
        true};
  }

  [[nodiscard]] ShadowGuardProjection project(const ChargeFrame& frame) const {
    return ShadowGuardProjection{
        "shadow-projection-" + stable_protocol_digest(frame.frame_id.value),
        "AuditLight"};
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }
};

}  // namespace asking_star::core::charge
