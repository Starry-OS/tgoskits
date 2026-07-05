#include "asking_star/gcyy/star_projection.hpp"

namespace asking_star::gcyy {

StarProjection::StarProjection(const YinOperator& yin,
                               const YangOperator& yang)
    : yin_(yin), yang_(yang) {}

GcyyResult StarProjection::project_to_gene(
    const DigitalSetFragment& fragment, const ProjectionContext& context,
    GeneView& out_gene) const {
  return yin_.compress(fragment, context, out_gene);
}

GcyyResult StarProjection::project_to_charge(
    const GeneView& gene, const ProjectionContext& context,
    ChargeView& out_charge) const {
  return yang_.expand(gene, context, out_charge);
}

GcyyResult StarProjection::make_cell(
    const GeneView& gene, const std::optional<ChargeView>& charge,
    const ProjectionContext& context, DigitalCell& out_cell) const {
  (void)context;
  out_cell.cell_id = "cell-" + gene.gene_id;
  out_cell.trace_id = gene.trace_id;
  out_cell.gene = gene;
  out_cell.charge = charge;
  out_cell.star_tag = gene.star_tag;
  out_cell.pointer_anchor = gene.source_pointer;
  out_cell.state = charge.has_value() ? DigitalCellState::ChargeReady
                                      : DigitalCellState::GeneReady;
  return out_cell.validate();
}

}  // namespace asking_star::gcyy

