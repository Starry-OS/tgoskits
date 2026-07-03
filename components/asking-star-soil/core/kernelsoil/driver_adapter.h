#pragma once

#include <string>

namespace asking_star::core::kernelsoil {

struct DriverRequest {
  std::string driver_id;
  std::string operation;

  [[nodiscard]] bool is_valid() const {
    return !driver_id.empty() && !operation.empty();
  }
};

class DriverAdapter {
 public:
  virtual ~DriverAdapter() = default;

  [[nodiscard]] virtual bool can_describe(
      const DriverRequest& request) const = 0;

  [[nodiscard]] bool is_interface_only() const {
    return true;
  }

  [[nodiscard]] bool executes_real_driver() const {
    return false;
  }

  [[nodiscard]] bool writes_genebank() const {
    return false;
  }
};

}  // namespace asking_star::core::kernelsoil
