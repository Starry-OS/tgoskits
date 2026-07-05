#pragma once

// EXPERIMENTAL ADAPTER ONLY.
// This file is not the official GCYY interface.
// Do not use this as the mainline DigitalSet/Gene/Charge/DigitalCell API.
// Mainline code must use the existing asking_star_gcyy interfaces and Record/View adapters.

#include "asking_star/gcyy/charge_record.hpp"
#include "asking_star/gcyy/digital_cell_record.hpp"
#include "asking_star/gcyy/gene_record.hpp"

namespace asking_star::v5 {

// Experimental spike adapter. Main GCYY code must use existing
// asking_star::gcyy::StarProjection until compatibility mapping is complete.
DigitalCellRecord make_digital_cell(const GeneRecord& gene,
                                    const ChargeRecord* charge = nullptr);

}  // namespace asking_star::v5
