#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"
#include "asking_star/gcyy/projection_context.hpp"
#include "asking_star/gcyy/star_runtime.hpp"

namespace asking_star::v56::compat {

class V55CoreBridge {
 public:
  [[nodiscard]] gcyy::GcyyResult project_to_cell(
      const gcyy::DigitalSetFragment& fragment,
      const gcyy::ProjectionContext& context,
      gcyy::DigitalCell& out_cell) const;

  [[nodiscard]] gcyy::GcyyResult run_cell(
      const gcyy::DigitalCell& cell,
      gcyy::DigitalCell& out_cell) const;

 private:
  gcyy::StarRuntime runtime_;
};

}  // namespace asking_star::v56::compat

