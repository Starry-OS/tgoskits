#include "asking_star/gcyy/star_runtime.hpp"

namespace asking_star::gcyy {

GcyyResult StarRuntime::interpret(const DigitalSetFragment& fragment,
                                  const ProjectionContext& context,
                                  StarRuntimeResult& out_result) const {
  StarProjection projection(yin_, yang_);
  auto gene_result = projection.project_to_gene(fragment, context,
                                                out_result.gene);
  if (!gene_result.ok()) {
    return gene_result;
  }
  auto charge_result = projection.project_to_charge(out_result.gene, context,
                                                    out_result.charge);
  if (!charge_result.ok()) {
    return charge_result;
  }
  return projection.make_cell(out_result.gene, out_result.charge, context,
                              out_result.cell);
}

}  // namespace asking_star::gcyy

