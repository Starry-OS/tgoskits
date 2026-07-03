#pragma once

#include "asking_star/gcyy/kernel_request.hpp"
#include "asking_star/gcyy/kernel_result.hpp"

namespace asking_star::gcyy {

// Mock adapter never calls syscall, ioctl, devices, StarryOS, RK3588, or AI.
class MockKernelAdapter {
 public:
  [[nodiscard]] KernelResult submit(const KernelRequest& request) const;
};

}  // namespace asking_star::gcyy

