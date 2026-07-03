#pragma once

#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/kernel_result.hpp"

namespace asking_star::gcyy {

class ReturnRebuilder {
 public:
  [[nodiscard]] GcyyResult rebuild(const KernelResult& result,
                                   DigitalSetFragment& out_fragment) const;
};

}  // namespace asking_star::gcyy

