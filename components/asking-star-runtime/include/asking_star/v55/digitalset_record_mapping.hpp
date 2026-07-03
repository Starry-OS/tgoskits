#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/v55/algebra_skeleton.hpp"
#include "asking_star/v55/chamber_pouch.hpp"
#include "asking_star/v55/chamber_runtime.hpp"
#include "asking_star/v55/reflex_gene_bank.hpp"
#include "asking_star/v55/walker_giant_ingress.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

using v5::DigitalSetRecordHeader;
using v5::DigitalSetRefRecord;
using v5::RecordTypeTag;

inline DigitalSetRecordHeader make_v55_header(std::uint64_t record_id,
                                              RecordTypeTag tag,
                                              const std::string& trace_id) {
  DigitalSetRecordHeader header;
  header.record_id = record_id;
  header.type_tag = tag;
  header.version = 55;
  header.generation = 1;
  header.trace_id = trace_id;
  header.fingerprint = "v55";
  return header;
}

inline DigitalSetRefRecord make_v55_ref(const DigitalSetRecordHeader& header) {
  return v5::make_ref(header);
}

inline DigitalSetRecordHeader header_for(const AppIntentRecord& record) {
  return make_v55_header(record.intent_id, RecordTypeTag::Payload,
                         record.trace_id);
}

inline DigitalSetRecordHeader header_for(const TimelineJointRecord& record,
                                         const std::string& trace_id) {
  return make_v55_header(record.joint_id, RecordTypeTag::TimelineSlice,
                         trace_id);
}

inline DigitalSetRecordHeader header_for(const ChamberPlacementRecord& record,
                                         const std::string& trace_id) {
  return make_v55_header(record.placement_id, RecordTypeTag::Payload,
                         trace_id);
}

inline DigitalSetRecordHeader header_for(const ChamberPouchRecord& record,
                                         const std::string& trace_id) {
  return make_v55_header(record.pouch_id, RecordTypeTag::Payload, trace_id);
}

inline DigitalSetRecordHeader header_for(
    const ChamberReflexGeneRecord& record,
    const std::string& trace_id) {
  return make_v55_header(record.reflex_gene_id, RecordTypeTag::Gene,
                         trace_id);
}

inline bool ref_matches_header(const DigitalSetRefRecord& ref,
                               const DigitalSetRecordHeader& header) {
  return ref.record_id == header.record_id &&
         ref.expected_type_tag == header.type_tag &&
         ref.expected_generation == header.generation;
}

}  // namespace asking_star::v55
