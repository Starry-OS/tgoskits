#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/v55/app_gene_charge.hpp"

#include <string>

namespace asking_star::v55 {

inline asking_star::gcyy::DigitalCell make_digital_cell_for_sun(
    const AppGeneRecord& app_gene,
    const AppChargeRecord& app_charge) {
  asking_star::gcyy::DigitalCell cell;
  cell.cell_id = "v55-cell-" + std::to_string(app_charge.charge.charge_id);
  cell.trace_id = app_charge.charge.trace_id;
  cell.gene.gene_id = "v55-gene-" + std::to_string(app_gene.gene.gene_id);
  cell.gene.trace_id = app_gene.gene.trace_id;
  cell.gene.state_hash = app_gene.gene.compressed_payload;
  cell.gene.semantic_hash = app_gene.app_category;
  cell.gene.star_tag = "v55-app";
  cell.gene.source_pointer =
      std::to_string(app_gene.gene.source_fragment_ref.record_id);
  cell.gene.compression_kind = "app-gene";
  cell.gene.rule_version = "v55";

  asking_star::gcyy::ChargeView charge;
  charge.charge_id =
      "v55-charge-" + std::to_string(app_charge.charge.charge_id);
  charge.origin_gene_id = cell.gene.gene_id;
  charge.trace_id = app_charge.charge.trace_id;
  charge.projection_id = "v55-app-charge";
  charge.capability_kind = app_gene.app_category;
  charge.execution_intent = app_charge.charge.execution_intent;
  charge.runtime_budget = std::to_string(app_charge.charge.ttl_ticks);
  charge.priority = 1;
  charge.lifetime_tick = app_charge.charge.ttl_ticks;
  cell.charge = charge;
  cell.state = asking_star::gcyy::DigitalCellState::ChargeReady;
  return cell;
}

}  // namespace asking_star::v55
