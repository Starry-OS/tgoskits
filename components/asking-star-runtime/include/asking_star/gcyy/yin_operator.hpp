#pragma once

#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gene_view.hpp"
#include "asking_star/gcyy/projection_context.hpp"

namespace asking_star::gcyy {

// YinOperator compresses a DigitalSetFragment into a GeneView.
class YinOperator {
 public:
  virtual ~YinOperator() = default;
  [[nodiscard]] virtual GcyyResult compress(
      const DigitalSetFragment& fragment, const ProjectionContext& context,
      GeneView& out_gene) const = 0;
};

}  // namespace asking_star::gcyy

