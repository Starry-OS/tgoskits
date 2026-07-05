#pragma once

#include "asking_star/soil/adapters/kernel_adapter.hpp"

namespace asking_star::soil::adapters {

class MockKernelAdapter final : public KernelAdapter {
 public:
  [[nodiscard]] KernelResult execute(const KernelRequest& request) const override;
};

}  // namespace asking_star::soil::adapters

