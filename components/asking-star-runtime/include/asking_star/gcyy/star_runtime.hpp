#pragma once

#include "asking_star/gcyy/mock_yang_operator.hpp"
#include "asking_star/gcyy/mock_yin_operator.hpp"
#include "asking_star/gcyy/star_projection.hpp"

namespace asking_star::gcyy {

struct StarRuntimeResult {
  GeneView gene;
  ChargeView charge;
  DigitalCell cell;
};

// Minimal StarRuntime facade for Walker -> GCYY tests.
class StarRuntime {
 public:
  [[nodiscard]] GcyyResult interpret(const DigitalSetFragment& fragment,
                                     const ProjectionContext& context,
                                     StarRuntimeResult& out_result) const;

 private:
  MockYinOperator yin_;
  MockYangOperator yang_;
};

}  // namespace asking_star::gcyy

