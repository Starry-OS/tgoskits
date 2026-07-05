#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"
#include "asking_star/gcyy/projection_context.hpp"
#include "asking_star/v56/compat/v55_core_bridge.hpp"

namespace asking_star::v56::core {

struct AskingStarCoreResult {
  gcyy::DigitalCell cell;
  const char* backend_name{"v5.5"};
  bool copied_runtime{false};

  [[nodiscard]] bool is_valid() const;
};

class AskingStarCore {
 public:
  [[nodiscard]] const char* backend_name() const;

  [[nodiscard]] gcyy::GcyyResult project(
      const gcyy::DigitalSetFragment& fragment,
      const gcyy::ProjectionContext& context,
      AskingStarCoreResult& out_result) const;

 private:
  compat::V55CoreBridge backend_;
};

}  // namespace asking_star::v56::core
