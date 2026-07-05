#pragma once

#include "asking_star/soil/adapters/kernel_adapter.hpp"
#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"
#include "asking_star/soil/kernel_request.hpp"
#include "asking_star/soil/kernel_result.hpp"

namespace asking_star::v56::compat {

class V55SoilAdapterBridge {
 public:
  V55SoilAdapterBridge();
  explicit V55SoilAdapterBridge(
      const soil::adapters::KernelAdapter& adapter);

  [[nodiscard]] soil::KernelResult execute(
      const soil::KernelRequest& request) const;

 private:
  soil::adapters::MockKernelAdapter default_adapter_;
  const soil::adapters::KernelAdapter* adapter_{nullptr};
};

}  // namespace asking_star::v56::compat

