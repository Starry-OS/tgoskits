// EXPERIMENTAL ADAPTER ONLY.
// This file is not the official GCYY interface.
// Do not use this as the mainline DigitalSet/Gene/Charge/DigitalCell API.
// Mainline code must use the existing asking_star_gcyy interfaces and Record/View adapters.

#include "asking_star/gcyy/v5_star_projection.hpp"

namespace asking_star::v5 {

DigitalCellRecord make_digital_cell(const GeneRecord& gene,
                                    const ChargeRecord* charge) {
  DigitalCellRecord cell;
  cell.cell_id = gene.gene_id;
  cell.gene_ref = DigitalSetRefRecord{gene.gene_id,
                                      RecordTypeTag::Gene,
                                      1,
                                      0,
                                      {},
                                      gene.trace_id};
  if (charge != nullptr) {
    cell.charge_ref = DigitalSetRefRecord{charge->charge_id,
                                          RecordTypeTag::Charge,
                                          1,
                                          0,
                                          {},
                                          charge->trace_id};
  }
  cell.trace_id = gene.trace_id;
  return cell;
}

}  // namespace asking_star::v5
