#pragma once

#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/soil/kernel_result.hpp"

namespace asking_star::soil {

class ReturnRebuilder {
 public:
  [[nodiscard]] SoilExecutionStatus rebuild(
      const KernelResult& result,
      asking_star::gcyy::DigitalSetFragment& out_fragment) const;
};

}  // namespace asking_star::soil

