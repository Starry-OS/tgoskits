#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil::adapters {

struct StarryOSOperationMapping {
  OperationKind operation{OperationKind::Unknown};
  std::string starryos_target;
  bool dry_run_supported{false};
  bool first_real_supported{false};
};

class StarryOSOperationMap {
 public:
  [[nodiscard]] StarryOSOperationMapping map(OperationKind operation) const;
};

}  // namespace asking_star::soil::adapters

