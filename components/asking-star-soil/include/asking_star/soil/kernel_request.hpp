#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::soil {

struct KernelRequest {
  SoilRequestId request_id;
  std::string trace_id;
  std::string cell_id;
  std::string origin_gene_id;
  std::string origin_charge_id;
  OperationKind operation_kind{OperationKind::Unknown};
  std::string target_kind;
  std::string payload;
  std::string expected_result_kind;
  std::uint64_t timeout_budget{0};
  int priority{0};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] bool is_supported_mock_operation() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::soil

