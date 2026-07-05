#pragma once

// EXPERIMENTAL ADAPTER ONLY.
// This file is not the official GCYY interface.
// Do not use this as the mainline DigitalSet/Gene/Charge/DigitalCell API.
// Mainline code must use the existing asking_star_gcyy interfaces and Record/View adapters.

#include "asking_star/gcyy/gene_record.hpp"

namespace asking_star::v5 {

// Experimental spike adapter. Do not use as a formal GCYY interface; merge
// into existing asking_star::gcyy::GeneView after compatibility mapping.
struct GeneRecordView {
  GeneRecord record;
};

}  // namespace asking_star::v5
