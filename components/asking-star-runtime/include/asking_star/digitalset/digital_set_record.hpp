#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v5 {

// DigitalSetRecord is a DigitalSet internal record format. It is not the
// DigitalSet fact carrier itself and must not be used as a replacement store.
enum class RecordTypeTag {
  Primordial,
  Fragment,
  Gene,
  Charge,
  DigitalCell,
  TimelineAxis,
  TimelineSlice,
  WangSliceLane,
  Task,
  DagEdge,
  JoinGroup,
  Heat,
  SlidingWindow,
  OrganQueue,
  KernelRequest,
  KernelResult,
  Return,
  TraceEvent,
  Benchmark,
  Callback,
  Payload,
  TimeAxisSeed,
  TaskState,
  FailurePolicy,
  RetryPolicy,
  CancelGroup
};

struct DigitalSetRecordHeader {
  std::uint64_t record_id{0};
  RecordTypeTag type_tag{RecordTypeTag::Payload};
  std::uint32_t version{1};
  std::uint64_t generation{1};
  std::uint32_t permission{0};
  std::string trace_id;
  std::string fingerprint;
};

// Payload-bearing record decoded by C++ code. Ownership and identity stay in
// DigitalSetStore / DigitalSetRefRecord instead of raw object pointers.
struct DigitalSetRecord {
  DigitalSetRecordHeader header;
  std::string payload;
};

inline bool same_record_identity(const DigitalSetRecordHeader& lhs,
                                 const DigitalSetRecordHeader& rhs) {
  return lhs.record_id == rhs.record_id && lhs.type_tag == rhs.type_tag &&
         lhs.generation == rhs.generation;
}

}  // namespace asking_star::v5
