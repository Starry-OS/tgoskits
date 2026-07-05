#pragma once

#include "asking_star/soil/kernel_request.hpp"
#include "asking_star/soil/kernel_result.hpp"

namespace asking_star::soil::adapters {

class KernelAdapter {
 public:
  virtual ~KernelAdapter() = default;
  [[nodiscard]] virtual KernelResult execute(
      const KernelRequest& request) const = 0;
};

}  // namespace asking_star::soil::adapters

