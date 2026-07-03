#include "asking_star/gcyy/digital_cell_view.hpp"
#include "asking_star/organ/soil_forward_organ.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalCellView cell;
  cell.record.cell_id = 99;
  cell.record.trace_id = "trace-soil-forward";
  cell.record.gene_ref.record_id = 5;
  cell.record.charge_ref = asking_star::v5::DigitalSetRefRecord{};
  cell.record.charge_ref->record_id = 6;

  asking_star::v5::SoilForwardOrgan organ;
  const auto record = organ.build_request(cell, "hello");
  const auto request = asking_star::v5::to_kernel_request(record);

  assert(request.is_valid());
  assert(request.cell_id == "99");
  assert(request.origin_gene_id == "gene-5");
  assert(request.origin_charge_id == "charge-6");
  return 0;
}
