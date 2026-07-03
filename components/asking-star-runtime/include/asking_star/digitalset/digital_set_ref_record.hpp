#pragma once

#include "asking_star/digitalset/digital_set_record.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v5 {

// DigitalSetRefRecord is the logical reference format inside DigitalSet.
// It is intentionally not a pointer and not a standalone DigitalSet body.
struct DigitalSetRefRecord {
  std::uint64_t record_id{0};
  RecordTypeTag expected_type_tag{RecordTypeTag::Payload};
  std::uint64_t expected_generation{1};
  std::uint32_t permission_mask{0};
  std::string hash_hint;
  std::string trace_id;
};

inline DigitalSetRefRecord make_ref(const DigitalSetRecordHeader& header) {
  return DigitalSetRefRecord{header.record_id,
                             header.type_tag,
                             header.generation,
                             header.permission,
                             header.fingerprint,
                             header.trace_id};
}

}  // namespace asking_star::v5
