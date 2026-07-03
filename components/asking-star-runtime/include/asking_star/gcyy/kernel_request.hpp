#pragma once

#include <string>

namespace asking_star::gcyy {

struct KernelRequest {
  std::string request_id;
  std::string cell_id;
  std::string trace_id;
  std::string operation_kind{"mock.operation"};
  std::string payload_ref;
  bool dry_run{true};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

