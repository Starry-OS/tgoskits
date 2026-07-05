#pragma once

#include "asking_star/gcyy/charge_view.hpp"
#include "asking_star/gcyy/gene_view.hpp"
#include "asking_star/gcyy/projection_context.hpp"

namespace asking_star::gcyy {

// YangOperator expands a GeneView into a short-lived ChargeView.
class YangOperator {
 public:
  virtual ~YangOperator() = default;
  [[nodiscard]] virtual GcyyResult expand(
      const GeneView& gene, const ProjectionContext& context,
      ChargeView& out_charge) const = 0;
};

}  // namespace asking_star::gcyy

