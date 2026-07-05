// EXPERIMENTAL ADAPTER ONLY.
// This file is not the official GCYY interface.
// Do not use this as the mainline DigitalSet/Gene/Charge/DigitalCell API.
// Mainline code must use the existing asking_star_gcyy interfaces and Record/View adapters.

#include "asking_star/gcyy/v5_yin_operator.hpp"

namespace asking_star::v5 {

GeneRecord YinOperator::compress(const DigitalSetFragment& fragment) const {
  GeneRecord gene;
  gene.gene_id = fragment.header.record_id;
  gene.source_fragment_ref = make_ref(fragment.header);
  gene.compressed_payload = "gene:" + std::to_string(fragment.records.size());
  gene.trace_id = fragment.header.trace_id;
  return gene;
}

}  // namespace asking_star::v5
