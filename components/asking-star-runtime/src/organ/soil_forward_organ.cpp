#include "asking_star/organ/soil_forward_organ.hpp"

#include <string>

namespace asking_star::v5 {

KernelRequestRecord SoilForwardOrgan::build_request(
    const DigitalCellView& cell, std::string payload) const {
  KernelRequestRecord record;
  record.cell_ref.record_id = cell.record.cell_id;
  record.cell_ref.trace_id = cell.record.trace_id;
  record.origin_gene_id = "gene-" + std::to_string(cell.record.gene_ref.record_id);
  if (cell.record.charge_ref.has_value()) {
    record.origin_charge_id =
        "charge-" + std::to_string(cell.record.charge_ref->record_id);
  }
  record.payload = std::move(payload);
  record.adapter_mode = "DryRun";
  return record;
}

}  // namespace asking_star::v5
