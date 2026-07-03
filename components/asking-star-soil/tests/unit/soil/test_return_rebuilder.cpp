#include "asking_star/soil/return_rebuilder.hpp"

#include <cassert>

int main() {
  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  asking_star::soil::KernelResult ok{
      asking_star::soil::SoilRequestId{"request-1"},
      "trace-1",
      asking_star::soil::SoilExecutionStatus::Ok,
      "",
      "payload",
      4,
      "done"};
  assert(rebuilder.rebuild(ok, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == "trace-1");
  assert(fragment.star_tag == "soil.kernel_result.ok");

  asking_star::soil::KernelResult failed{
      asking_star::soil::SoilRequestId{"request-2"},
      "trace-2",
      asking_star::soil::SoilExecutionStatus::KernelFailed,
      "KernelFailed",
      "",
      0,
      "kernel failed"};
  assert(rebuilder.rebuild(failed, fragment) ==
         asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == "trace-2");
  assert(fragment.star_tag == "soil.kernel_result.error");
  return 0;
}

