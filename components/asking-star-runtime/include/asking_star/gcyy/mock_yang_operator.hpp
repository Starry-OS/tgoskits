#pragma once

#include "asking_star/gcyy/yang_operator.hpp"

namespace asking_star::gcyy {

// Mock Yang implementation for deterministic Round 2/3 tests.
class MockYangOperator final : public YangOperator {
 public:
  [[nodiscard]] GcyyResult expand(const GeneView& gene,
                                  const ProjectionContext& context,
                                  ChargeView& out_charge) const override;
};

}  // namespace asking_star::gcyy

