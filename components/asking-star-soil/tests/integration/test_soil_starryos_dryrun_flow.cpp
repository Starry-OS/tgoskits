#include "asking_star/soil/adapters/starryos_adapter.hpp"
#include "asking_star/soil/return_rebuilder.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>

int main() {
  asking_star::soil::SoilRuntime soil;
  auto cell = asking_star::tests::soil::make_soil_test_cell();
  auto request = soil.make_request(cell, asking_star::soil::OperationKind::LogWrite,
                                  "starryos.console", "hello starryos");

  asking_star::soil::adapters::StarryOSAdapter adapter{
      {false, asking_star::soil::adapters::StarryOSAdapterMode::DryRun}};
  auto result = adapter.execute(request);
  assert(result.ok());
  assert(result.trace_id == request.trace_id);
  assert(result.request_id.value == request.request_id.value);

  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  assert(rebuilder.rebuild(result, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == request.trace_id);
  return 0;
}

