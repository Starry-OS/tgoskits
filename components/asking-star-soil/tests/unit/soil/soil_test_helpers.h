#pragma once

#include "asking_star/gcyy/digital_cell.hpp"

namespace asking_star::tests::soil {

inline asking_star::gcyy::DigitalCell make_soil_test_cell() {
  asking_star::gcyy::GeneView gene;
  gene.gene_id = "gene-soil";
  gene.trace_id = "trace-soil";
  gene.state_hash = "state-soil";
  gene.semantic_hash = "semantic-soil";

  asking_star::gcyy::ChargeView charge;
  charge.charge_id = "charge-soil";
  charge.origin_gene_id = gene.gene_id;
  charge.trace_id = "trace-soil";
  charge.capability_kind = "mock.execute";

  asking_star::gcyy::DigitalCell cell;
  cell.cell_id = "cell-soil";
  cell.trace_id = "trace-soil";
  cell.gene = gene;
  cell.charge = charge;
  cell.state = asking_star::gcyy::DigitalCellState::ChargeReady;
  return cell;
}

}  // namespace asking_star::tests::soil

