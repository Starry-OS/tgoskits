#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil {

struct SyscallPlan {
  OperationKind operation{OperationKind::Unknown};
  std::string plan_id;
  bool dry_run{true};

  [[nodiscard]] bool is_valid() const {
    return !plan_id.empty() && operation != OperationKind::Unknown && dry_run;
  }
};

}  // namespace asking_star::soil

