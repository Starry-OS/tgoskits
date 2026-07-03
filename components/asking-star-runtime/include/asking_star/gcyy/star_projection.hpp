#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/yin_operator.hpp"
#include "asking_star/gcyy/yang_operator.hpp"

#include <optional>

namespace asking_star::gcyy {

// StarProjection wires Yin/Yang without touching Soil or KernelAdapter.
class StarProjection {
 public:
  StarProjection(const YinOperator& yin, const YangOperator& yang);

  [[nodiscard]] GcyyResult project_to_gene(
      const DigitalSetFragment& fragment, const ProjectionContext& context,
      GeneView& out_gene) const;
  [[nodiscard]] GcyyResult project_to_charge(
      const GeneView& gene, const ProjectionContext& context,
      ChargeView& out_charge) const;
  [[nodiscard]] GcyyResult make_cell(
      const GeneView& gene, const std::optional<ChargeView>& charge,
      const ProjectionContext& context, DigitalCell& out_cell) const;

 private:
  const YinOperator& yin_;
  const YangOperator& yang_;
};

}  // namespace asking_star::gcyy
