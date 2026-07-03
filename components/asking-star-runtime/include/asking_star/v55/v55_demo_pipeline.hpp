#pragma once

#include "asking_star/v55/algebra_skeleton.hpp"
#include "asking_star/v55/skin_ui_projection.hpp"
#include "asking_star/v55/soil_multichamber_adapter.hpp"

#include <string>
#include <vector>

namespace asking_star::v55 {

struct V55DemoResult {
  std::string skin_json;
  AdapterMode adapter_mode{AdapterMode::Mock};
  bool board_real_claim{false};
  bool preset_requires_sun_admission{true};
  bool reflex_hit{false};
};

class V55DemoPipeline {
 public:
  [[nodiscard]] V55DemoResult run(WalkerInputKind input_kind,
                                  AdapterMode requested_mode) const {
    WalkerInputRecord input{90, input_kind, "demo-payload", "v55-demo"};
    const WalkerIngress ingress;
    const auto fragment = ingress.accept(input);
    const auto intent = make_app_intent(input);

    const AppGeneBuilder gene_builder;
    const auto gene = gene_builder.build(intent, fragment.header.record_id);
    const AppChargeBuilder charge_builder;
    const auto charge = charge_builder.build(gene, 2);

    MainTimeAxisRecord axis{700, 10, 1, 1, {}};
    AlgebraSkeleton skeleton(axis);
    auto joint = skeleton.make_joint(701, 1);
    mount_ref(joint,
              JointRefRole::AppCharge,
              charge.charge.gene_ref);

    const auto chamber_kind = kind_for(input_kind, requested_mode);
    const ChamberProfileRecord chamber{11,
                                       chamber_kind,
                                       requested_mode,
                                       "demo",
                                       requested_mode == AdapterMode::BoardReal
                                           ? 3U
                                           : 0U};
    const ChamberPlacementPolicy placement_policy;
    const auto placement = placement_policy.select(gene, charge, {chamber});

    const ChamberExecutionRecord execution{800,
                                           placement.placement_id,
                                           placement.adapter_mode,
                                           charge.charge.execution_intent};
    const SoilMultiChamberAdapter soil;
    const auto soil_result = soil.execute(execution);

    const ChamberPouchView pouch_view;
    const auto pouch = pouch_view.observe(execution, soil_result.payload, true);

    ReflexGeneBank bank;
    const auto reflex = bank.compress(pouch);
    const auto preset = bank.expand(reflex);

    const SkinStateProjectionRecord state{1,
                                          joint.joint_id,
                                          placement.selected_chamber_id,
                                          pouch.health,
                                          "trace-recorded",
                                          reflex.confidence > 0.5,
                                          placement.adapter_mode};
    const SkinUIProjection skin;

    V55DemoResult result;
    result.skin_json = skin.to_json(state);
    result.adapter_mode = placement.adapter_mode;
    result.board_real_claim = soil_result.board_real_claim;
    result.preset_requires_sun_admission = preset.requires_sun_admission;
    result.reflex_hit = state.reflex_hit;
    return result;
  }

 private:
  [[nodiscard]] static ChamberKind kind_for(WalkerInputKind input_kind,
                                            AdapterMode mode) {
    if (mode == AdapterMode::DryRun) {
      return ChamberKind::StableStarry;
    }
    if (input_kind == WalkerInputKind::Replay ||
        input_kind == WalkerInputKind::AiResult) {
      return ChamberKind::Replay;
    }
    return ChamberKind::Mock;
  }
};

}  // namespace asking_star::v55
