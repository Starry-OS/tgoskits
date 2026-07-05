#include "asking_star/gcyy/digital_cell.hpp"

#include <cassert>
#include <string>

namespace {

asking_star::gcyy::GeneView make_gene() {
  asking_star::gcyy::GeneView gene;
  gene.gene_id = "gene-1";
  gene.trace_id = "trace-1";
  gene.state_hash = "state-hash";
  gene.semantic_hash = "semantic-hash";
  gene.star_tag = "input.text";
  return gene;
}

asking_star::gcyy::ChargeView make_charge() {
  asking_star::gcyy::ChargeView charge;
  charge.charge_id = "charge-1";
  charge.origin_gene_id = "gene-1";
  charge.trace_id = "trace-1";
  charge.capability_kind = "mock.execute";
  return charge;
}

}  // namespace

int main() {
  asking_star::gcyy::DigitalCell gene_only;
  gene_only.cell_id = "cell-1";
  gene_only.trace_id = "trace-1";
  gene_only.gene = make_gene();
  gene_only.star_tag = "input.text";
  gene_only.state = asking_star::gcyy::DigitalCellState::GeneReady;

  assert(gene_only.has_trace());
  assert(!gene_only.has_charge());
  assert(gene_only.validate().ok());
  assert(gene_only.debug_dump().find("has_charge=false") != std::string::npos);

  auto with_charge = gene_only;
  with_charge.charge = make_charge();
  with_charge.state = asking_star::gcyy::DigitalCellState::ChargeReady;
  assert(with_charge.has_charge());
  assert(with_charge.validate().ok());
  assert(with_charge.debug_dump().find("charge_ready") != std::string::npos);

  with_charge.charge->origin_gene_id = "other-gene";
  auto invalid = with_charge.validate();
  assert(!invalid.ok());
  assert(invalid.status == asking_star::gcyy::GcyyStatus::InvalidState);

  gene_only.trace_id.clear();
  auto missing_trace = gene_only.validate();
  assert(!missing_trace.ok());
  assert(missing_trace.status == asking_star::gcyy::GcyyStatus::MissingTraceId);

  return 0;
}

