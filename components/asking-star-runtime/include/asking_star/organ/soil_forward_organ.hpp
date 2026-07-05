#pragma once

#include "asking_star/gcyy/digital_cell_view.hpp"
#include "asking_star/soil/kernel_request_record.hpp"

namespace asking_star::v5 {

// SoilForwardOrgan converts an admitted DigitalCellView to KernelRequestRecord.
// It does not call StarryOS/Linux adapters; SoilRuntime remains the OS boundary.
class SoilForwardOrgan {
 public:
  [[nodiscard]] KernelRequestRecord build_request(
      const DigitalCellView& cell, std::string payload = "mainline payload") const;
};

}  // namespace asking_star::v5
