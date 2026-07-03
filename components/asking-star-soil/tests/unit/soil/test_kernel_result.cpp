#include "asking_star/soil/kernel_result.hpp"

#include <cassert>

int main() {
  asking_star::soil::KernelResult ok{
      asking_star::soil::SoilRequestId{"request-1"},
      "trace-1",
      asking_star::soil::SoilExecutionStatus::Ok,
      "",
      "payload",
      7,
      "done"};
  assert(ok.ok());
  assert(ok.is_valid());
  assert(ok.error().ok());

  asking_star::soil::KernelResult failed{
      asking_star::soil::SoilRequestId{"request-1"},
      "trace-1",
      asking_star::soil::SoilExecutionStatus::UnsupportedOperation,
      "UnsupportedOperation",
      "",
      0,
      "not supported"};
  assert(!failed.ok());
  assert(failed.is_valid());
  assert(!failed.error().ok());
  return 0;
}

