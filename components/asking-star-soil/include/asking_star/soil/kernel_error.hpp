#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil {

struct KernelError {
  SoilExecutionStatus status{SoilExecutionStatus::Ok};
  std::string code;
  std::string message;

  [[nodiscard]] bool ok() const { return is_success(status); }
  [[nodiscard]] bool is_valid() const {
    return ok() || (!code.empty() && !message.empty());
  }
};

}  // namespace asking_star::soil

