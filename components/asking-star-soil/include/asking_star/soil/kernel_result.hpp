#pragma once

#include "asking_star/soil/kernel_error.hpp"
#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil {

struct KernelResult {
  SoilRequestId request_id;
  std::string trace_id;
  SoilExecutionStatus status{SoilExecutionStatus::Ok};
  std::string error_code;
  std::string payload;
  std::uint64_t latency_ns{0};
  std::string message;

  [[nodiscard]] bool ok() const;
  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] KernelError error() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::soil

