#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <string>

namespace asking_star::gcyy {

struct KernelResult {
  std::string result_id;
  std::string request_id;
  std::string trace_id;
  GcyyStatus status{GcyyStatus::Ok};
  std::string payload_ref;
  std::string error_code;
  bool dry_run{true};

  [[nodiscard]] bool ok() const;
  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

