#include "asking_star/gcyy/mock_yang_operator.hpp"

namespace asking_star::gcyy {

GcyyResult MockYangOperator::expand(const GeneView& gene,
                                    const ProjectionContext& context,
                                    ChargeView& out_charge) const {
  auto gene_result = gene.validate();
  if (!gene_result.ok()) {
    return gene_result;
  }
  auto context_result = context.validate();
  if (!context_result.ok()) {
    return context_result;
  }
  out_charge.charge_id = "charge-" + gene.gene_id;
  out_charge.origin_gene_id = gene.gene_id;
  out_charge.trace_id = gene.trace_id;
  out_charge.projection_id = context.context_id;
  out_charge.capability_kind = "mock.execute";
  out_charge.execution_intent = "mock execution for " + gene.gene_id;
  out_charge.runtime_budget = context.budget_ref;
  out_charge.priority = context.mode == ProjectionMode::AskingStar ? 10 : 1;
  out_charge.payload_ref = "payload://" + gene.gene_id;
  out_charge.lifetime_tick = 100;
  return out_charge.validate();
}

}  // namespace asking_star::gcyy

