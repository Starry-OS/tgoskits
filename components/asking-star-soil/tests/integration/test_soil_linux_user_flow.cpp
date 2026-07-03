#include "asking_star/soil/adapters/linux_user_adapter.hpp"
#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"
#include "asking_star/soil/return_rebuilder.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "tests/unit/soil/soil_test_helpers.h"

#include <cassert>

int main() {
  asking_star::soil::SoilRuntime soil;
  auto cell = asking_star::tests::soil::make_soil_test_cell();

  auto write = soil.make_request(cell, asking_star::soil::OperationKind::FileWrite,
                                 "flow.txt", "flow payload");
  asking_star::soil::adapters::LinuxUserAdapter linux_adapter{
      "runtime_tmp/round14-flow"};
  auto write_result = linux_adapter.execute(write);
  assert(write_result.ok());

  auto read = soil.make_request(cell, asking_star::soil::OperationKind::FileRead,
                                "flow.txt", "");
  auto read_result = linux_adapter.execute(read);
  assert(read_result.ok());
  assert(read_result.payload == "flow payload");

  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  assert(rebuilder.rebuild(read_result, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == read.trace_id);

  asking_star::soil::adapters::MockKernelAdapter mock_adapter;
  auto mock_result = mock_adapter.execute(
      soil.make_request(cell, asking_star::soil::OperationKind::LogWrite,
                        "mock.log", "mock payload"));
  assert(mock_result.ok());
  return 0;
}

