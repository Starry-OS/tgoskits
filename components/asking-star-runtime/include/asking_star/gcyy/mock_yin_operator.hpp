#pragma once

#include "asking_star/gcyy/yin_operator.hpp"

namespace asking_star::gcyy {

// Mock Yin implementation for deterministic Round 2/3 tests.
class MockYinOperator final : public YinOperator {
 public:
  [[nodiscard]] GcyyResult compress(
      const DigitalSetFragment& fragment, const ProjectionContext& context,
      GeneView& out_gene) const override;
};

[[nodiscard]] std::string make_mock_gene_hash(
    const DigitalSetFragment& fragment);

}  // namespace asking_star::gcyy

