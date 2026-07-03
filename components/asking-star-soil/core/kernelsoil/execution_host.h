#pragma once

#include "core/kernelsoil/soil_result.h"

#include <string>

namespace asking_star::core::kernelsoil {

struct ExecutionHostRequest {
  std::string host_id;
  std::string capability;

  [[nodiscard]] bool is_valid() const {
    return !host_id.empty() && !capability.empty();
  }
};

class ExecutionHost {
 public:
  virtual ~ExecutionHost() = default;

  [[nodiscard]] virtual SoilResult execute(const SoilRequest& request) const = 0;

  [[nodiscard]] virtual bool accepts(
      const ExecutionHostRequest& request) const {
    return request.is_valid();
  }

  [[nodiscard]] bool is_interface_only() const {
    return true;
  }

  [[nodiscard]] bool writes_genebank() const {
    return false;
  }

  [[nodiscard]] bool used_by_scheduler() const {
    return false;
  }
};

class DryRunExecutionHost final : public ExecutionHost {
 public:
  [[nodiscard]] SoilResult execute(const SoilRequest& request) const override {
    return executor_.dispatch(request);
  }

  [[nodiscard]] bool accepts(
      const ExecutionHostRequest& request) const override {
    return request.is_valid();
  }

 private:
  DryRunSoilExecutor executor_;
};

}  // namespace asking_star::core::kernelsoil
