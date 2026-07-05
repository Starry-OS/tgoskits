#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil {

struct DeviceRequest {
  std::string target_kind;
  OperationKind operation{OperationKind::Unknown};
  std::string payload;

  [[nodiscard]] bool is_valid() const {
    return !target_kind.empty() && operation != OperationKind::Unknown;
  }
};

}  // namespace asking_star::soil

