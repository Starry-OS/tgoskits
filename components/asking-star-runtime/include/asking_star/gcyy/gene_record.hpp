#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v5 {

// GeneRecord is the DigitalSet record form for a compressed Gene.
struct GeneRecord {
  std::uint64_t gene_id{0};
  DigitalSetRefRecord source_fragment_ref;
  std::string compressed_payload;
  std::string trace_id;
};

}  // namespace asking_star::v5
