#include "asking_star/v55/app_gene_charge.hpp"
#include "asking_star/v55/chamber_starryos_dryrun_bridge.hpp"
#include "asking_star/v55/pouch_trace_bridge.hpp"
#include "asking_star/v55/walker_giant_ingress.hpp"

#include <cassert>
#include <string>
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
  using asking_star::v55::ChamberStarryOSDryRunBridge;
  using asking_star::v55::PouchTraceBridge;
  using asking_star::v55::WalkerInputKind;
  using asking_star::v55::WalkerInputRecord;
  using asking_star::v55::make_app_intent;

  const WalkerInputRecord input{111, WalkerInputKind::Command,
                                "echo stable starry", "trace-stable-starry"};
  const auto intent = make_app_intent(input);
  const AppGeneBuilder gene_builder;
  const auto app_gene = gene_builder.build(intent, 111);
  const AppChargeBuilder charge_builder;
  const auto app_charge = charge_builder.build(app_gene, 3);

  const std::vector<ChamberProfileRecord> chambers{
      {1, ChamberKind::StableStarry, AdapterMode::DryRun, "starryos.console", 1},
      {2, ChamberKind::Mock, AdapterMode::Mock, "fallback", 0}};
  const ChamberPlacementPolicy placement_policy;
  const auto placement =
      placement_policy.select(app_gene, app_charge, chambers);
  assert(placement.selected_chamber_id == 1);
  assert(placement.adapter_mode == AdapterMode::DryRun);

  const ChamberExecutionRecord execution{112, placement.placement_id,
                                         placement.adapter_mode,
                                         "uart stable-starry dryrun"};
  const ChamberStarryOSDryRunBridge starryos_bridge;
  const auto starryos = starryos_bridge.execute(execution);
  assert(starryos.qemu_ready);
  assert(!starryos.board_real_claim);

  const ChamberPouchView pouch_view;
  const auto pouch = pouch_view.observe(execution, starryos.result.payload, true);
  const PouchTraceBridge trace_bridge;
  const auto trace = trace_bridge.record(execution, pouch, starryos, 11);
  assert(trace.trace_complete);
  assert(trace.event.adapter_mode == "DryRun");
  assert(trace.event.status == "healthy");
  assert(!trace.board_real_claim);

  return 0;
}
