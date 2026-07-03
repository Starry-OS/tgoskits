#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"
#include "asking_star/soil/return_rebuilder.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>

int main() {
  asking_star::soil::SoilRuntime soil;
  auto cell = asking_star::tests::soil::make_soil_test_cell();
  auto request = soil.make_request(cell, asking_star::soil::OperationKind::LogWrite,
                                  "mock.log", "hello");
  auto packet = soil.make_abi_packet(request);
  assert(packet.is_valid());

  asking_star::soil::adapters::MockKernelAdapter adapter;
  auto result = adapter.execute(request);
  assert(result.ok());
  assert(result.request_id.value == request.request_id.value);
  assert(result.trace_id == request.trace_id);

  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  assert(rebuilder.rebuild(result, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == request.trace_id);

  asking_star::soil::KernelRequest invalid;
  auto invalid_result = adapter.execute(invalid);
  assert(invalid_result.status ==
         asking_star::soil::SoilExecutionStatus::InvalidRequest);

  auto unsupported =
      soil.make_request(cell, asking_star::soil::OperationKind::Unknown,
                        "mock.unknown", "payload");
  auto unsupported_result = adapter.execute(unsupported);
  assert(unsupported_result.status ==
         asking_star::soil::SoilExecutionStatus::UnsupportedOperation);
  return 0;
}
