#include "asking_star/gcyy/digital_cell_view.hpp"
#include "asking_star/organ/soil_forward_organ.hpp"
#include "asking_star/soil/adapters/mock_kernel_adapter.hpp"
#include "asking_star/soil/return_rebuilder.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalCellView cell;
  cell.record.cell_id = 100;
  cell.record.trace_id = "trace-return";
  cell.record.gene_ref.record_id = 7;

  asking_star::v5::SoilForwardOrgan organ;
  const auto request_record = organ.build_request(cell, "payload");
  const auto request = asking_star::v5::to_kernel_request(request_record);
  asking_star::soil::adapters::MockKernelAdapter adapter;
  const auto result = adapter.execute(request);
  asking_star::soil::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  const auto rebuild_status = rebuilder.rebuild(result, fragment);

  assert(result.is_valid());
  assert(rebuild_status == asking_star::soil::SoilExecutionStatus::Ok);
  assert(fragment.trace_id == "trace-return");
  assert(!fragment.star_tag.empty());
  return 0;
}
