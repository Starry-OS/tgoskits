// EXPERIMENTAL ADAPTER ONLY.
// This file is not the official GCYY interface.
// Do not use this as the mainline DigitalSet/Gene/Charge/DigitalCell API.
// Mainline code must use the existing asking_star_gcyy interfaces and Record/View adapters.

#include "asking_star/gcyy/v5_yang_operator.hpp"

namespace asking_star::v5 {

ChargeRecord YangOperator::expand(const GeneRecord& gene) const {
  ChargeRecord charge;
  charge.charge_id = gene.gene_id;
  charge.gene_ref = DigitalSetRefRecord{gene.gene_id,
                                        RecordTypeTag::Gene,
                                        1,
                                        0,
                                        {},
                                        gene.trace_id};
  charge.execution_intent = "execute:" + gene.compressed_payload;
  charge.ttl_ticks = 1;
  charge.trace_id = gene.trace_id;
  return charge;
}

}  // namespace asking_star::v5
