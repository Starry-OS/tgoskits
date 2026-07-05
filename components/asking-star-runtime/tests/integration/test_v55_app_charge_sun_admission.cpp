#include "asking_star/gcyy/sun_orchestrator.hpp"
#include "asking_star/v55/app_charge_sun_bridge.hpp"

#include <cassert>

int main() {
  using asking_star::gcyy::RuntimeBudget;
  using asking_star::gcyy::SunOrchestrator;
  using asking_star::v55::AppChargeBuilder;
  using asking_star::v55::AppGeneBuilder;
  using asking_star::v55::WalkerInputKind;
  using asking_star::v55::WalkerInputRecord;
  using asking_star::v55::make_app_intent;
  using asking_star::v55::make_digital_cell_for_sun;

  WalkerInputRecord input{55, WalkerInputKind::Command, "echo v55", "v55-q3"};
  const auto intent = make_app_intent(input);
  const AppGeneBuilder gene_builder;
  const auto app_gene = gene_builder.build(intent, 55);
  const AppChargeBuilder charge_builder;
  const auto app_charge = charge_builder.build(app_gene, 2);
  assert(app_charge.requires_sun_admission);

  const auto cell = make_digital_cell_for_sun(app_gene, app_charge);
  assert(cell.validate().ok());

  SunOrchestrator sun;
  const RuntimeBudget allowed{"budget-ok", "v55-q3", 1, 1};
  assert(sun.admit(cell, allowed).ok());

  const RuntimeBudget denied{"budget-denied", "v55-q3", 0, 0};
  assert(!sun.admit(cell, denied).ok());
  return 0;
}
