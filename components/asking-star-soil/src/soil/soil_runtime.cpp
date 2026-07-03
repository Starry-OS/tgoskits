#include "asking_star/soil/soil_runtime.hpp"

#include <utility>

namespace asking_star::soil {

KernelRequest SoilRuntime::make_request(
    const asking_star::gcyy::DigitalCell& cell, OperationKind operation,
    std::string target_kind, std::string payload) const {
  KernelRequest request;
  request.request_id = SoilRequestId{"soil-request-" + cell.cell_id};
  request.trace_id = cell.trace_id;
  request.cell_id = cell.cell_id;
  request.origin_gene_id = cell.gene.gene_id;
  request.origin_charge_id = cell.charge.has_value() ? cell.charge->charge_id
                                                     : "";
  request.operation_kind = operation;
  request.target_kind = std::move(target_kind);
  request.payload = std::move(payload);
  request.expected_result_kind = "DigitalSetFragment";
  request.timeout_budget = 1000000;
  request.priority = 0;
  return request;
}

AbiPacket SoilRuntime::make_abi_packet(const KernelRequest& request) const {
  return asking_star::soil::make_abi_packet(request);
}

}  // namespace asking_star::soil

