#include "asking_star/soil/kernel_request.hpp"

#include <sstream>

namespace asking_star::soil {

bool KernelRequest::is_valid() const {
  return request_id.is_valid() && !trace_id.empty() && !cell_id.empty() &&
         !origin_gene_id.empty() && operation_kind != OperationKind::Unknown &&
         !target_kind.empty() && !expected_result_kind.empty();
}

bool KernelRequest::is_supported_mock_operation() const {
  return operation_kind == OperationKind::LogWrite ||
         operation_kind == OperationKind::FileWrite ||
         operation_kind == OperationKind::FileRead ||
         operation_kind == OperationKind::Noop ||
         operation_kind == OperationKind::UartWrite ||
         operation_kind == OperationKind::DeviceIoctl;
}

std::string KernelRequest::debug_dump() const {
  std::ostringstream out;
  out << "KernelRequest{id=" << request_id.value << ", trace=" << trace_id
      << ", cell=" << cell_id << ", gene=" << origin_gene_id
      << ", charge=" << origin_charge_id << ", op="
      << to_string(operation_kind) << ", target=" << target_kind << "}";
  return out.str();
}

}  // namespace asking_star::soil

