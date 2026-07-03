#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>

int main() {
  asking_star::soil::SoilRuntime soil;
  auto cell = asking_star::tests::soil::make_soil_test_cell();
  auto request = soil.make_request(cell, asking_star::soil::OperationKind::LogWrite,
                                  "mock.log", "hello");
  assert(request.is_valid());
  assert(request.request_id.value == "soil-request-cell-soil");
  assert(request.trace_id == "trace-soil");
  assert(request.cell_id == "cell-soil");
  assert(request.origin_gene_id == "gene-soil");
  assert(request.origin_charge_id == "charge-soil");
  assert(request.expected_result_kind == "DigitalSetFragment");

  auto packet = soil.make_abi_packet(request);
  assert(packet.is_valid());
  assert(packet.request_id.value == request.request_id.value);
  assert(packet.trace_id == request.trace_id);
  assert(packet.payload.size() == request.payload.size());
  return 0;
}

