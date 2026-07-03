#pragma once

#include "asking_star/soil/adapters/kernel_adapter.hpp"
#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"
#include "asking_star/soil/adapters/starryos_build_config.hpp"
#include "asking_star/soil/adapters/starryos_operation_map.hpp"
#include "asking_star/soil/adapters/starryos_platform.hpp"

namespace asking_star::soil::adapters {

class StarryOSAdapter final : public KernelAdapter {
 public:
  explicit StarryOSAdapter(StarryOSBuildConfig config = {});

  [[nodiscard]] KernelResult execute(const KernelRequest& request) const override;
  [[nodiscard]] const StarryOSBuildConfig& config() const;

 private:
  [[nodiscard]] KernelResult dry_run(const KernelRequest& request) const;
  [[nodiscard]] KernelResult host_mock(const KernelRequest& request) const;
  [[nodiscard]] KernelResult board_real(const KernelRequest& request) const;
  [[nodiscard]] KernelResult from_platform_result(
      const KernelRequest& request,
      const StarryOSPlatformResult& platform_result) const;

  StarryOSBuildConfig config_;
  StarryOSOperationMap operation_map_;
  StarryOSPlatform platform_;
};

}  // namespace asking_star::soil::adapters
