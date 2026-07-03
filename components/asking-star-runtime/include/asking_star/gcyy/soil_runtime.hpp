#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/kernel_request.hpp"

namespace asking_star::gcyy {

class SoilRuntime {
 public:
  [[nodiscard]] GcyyResult make_request(const DigitalCell& cell,
                                        KernelRequest& out_request) const;
};

}  // namespace asking_star::gcyy

