#pragma once

#include "asking_star/gcyy/digital_cell_record.hpp"
#include "asking_star/soil/kernel_request.hpp"

namespace asking_star::v5 {

struct KernelRequestRecord {
  DigitalSetRefRecord cell_ref;
  std::string origin_gene_id;
  std::string origin_charge_id;
  asking_star::soil::OperationKind operation{
      asking_star::soil::OperationKind::LogWrite};
  std::string target_kind{"mock.log"};
  std::string payload{"mock payload"};
  std::string adapter_mode{"Mock"};
};

inline asking_star::soil::KernelRequest to_kernel_request(
    const KernelRequestRecord& record) {
  asking_star::soil::KernelRequest request;
  request.request_id.value = "soil-" + std::to_string(record.cell_ref.record_id);
  request.trace_id = record.cell_ref.trace_id;
  request.cell_id = std::to_string(record.cell_ref.record_id);
  request.origin_gene_id = record.origin_gene_id;
  request.origin_charge_id = record.origin_charge_id;
  request.operation_kind = record.operation;
  request.target_kind = record.target_kind;
  request.payload = record.payload;
  request.expected_result_kind = "DigitalSetFragment";
  request.timeout_budget = 1000000;
  return request;
}

}  // namespace asking_star::v5
