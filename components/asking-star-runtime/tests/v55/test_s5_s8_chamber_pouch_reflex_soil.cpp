#include "asking_star/v55/reflex_gene_bank.hpp"
#include "asking_star/v55/soil_multichamber_adapter.hpp"

#include <cassert>
#include <vector>

int main() {
  using asking_star::v55::AdapterMode;
  using asking_star::v55::AppChargeBuilder;
  using asking_star::v55::AppGeneBuilder;
  using asking_star::v55::ChamberExecutionRecord;
  using asking_star::v55::ChamberKind;
  using asking_star::v55::ChamberPlacementPolicy;
  using asking_star::v55::ChamberPouchView;
  using asking_star::v55::ChamberProfileRecord;
  using asking_star::v55::ReflexGeneBank;
  using asking_star::v55::SoilMultiChamberAdapter;
  using asking_star::v55::WalkerInputKind;
  using asking_star::v55::WalkerInputRecord;
  using asking_star::v55::make_app_intent;

  WalkerInputRecord input{7, WalkerInputKind::Replay, "replay-ai", "v55-s5-s8"};
  const auto intent = make_app_intent(input);
  const AppGeneBuilder gene_builder;
  const auto gene = gene_builder.build(intent, 7);
  const AppChargeBuilder charge_builder;
  const auto charge = charge_builder.build(gene, 2);

  std::vector<ChamberProfileRecord> chambers = {
      {1, ChamberKind::Mock, AdapterMode::Mock, "safe-host", 0},
      {2, ChamberKind::Replay, AdapterMode::Replay, "replay-ai", 0},
      {3, ChamberKind::StableStarry, AdapterMode::DryRun, "log-write", 1}};

  const ChamberPlacementPolicy placement_policy;
  const auto placement = placement_policy.select(gene, charge, chambers);
  assert(placement.selected_chamber_id == 2);
  assert(placement.requires_sun_admission);
  assert(placement.adapter_mode == AdapterMode::Replay);

  ChamberExecutionRecord execution{20,
                                   placement.placement_id,
                                   placement.adapter_mode,
                                   charge.charge.execution_intent};
  const SoilMultiChamberAdapter soil;
  const auto soil_result = soil.execute(execution);
  assert(!soil_result.board_real_claim);

  const ChamberPouchView pouch_view;
  const auto pouch = pouch_view.observe(execution, soil_result.payload, true);
  assert(pouch.reflex_candidate);

  ReflexGeneBank bank;
  const auto reflex = bank.compress(pouch);
  const auto preset = bank.expand(reflex);
  assert(reflex.confidence > 0.5);
  assert(preset.requires_sun_admission);
  return 0;
}
