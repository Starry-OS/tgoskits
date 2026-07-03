#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <array>
#include <cstdint>
#include <string>

namespace asking_star::v55 {

using v5::DigitalSetRefRecord;
using v5::RecordTypeTag;

enum class SeedRefKind {
  TimeAxis,
  ChamberRegistry,
  ReflexBank,
  TraceStore,
};

struct NamedSeedRef {
  SeedRefKind kind{SeedRefKind::TimeAxis};
  DigitalSetRefRecord ref{};
};

struct PrimordialSeedRefsRecord {
  std::uint32_t version{1};
  DigitalSetRefRecord time_axis_seed_ref{};
  DigitalSetRefRecord chamber_registry_seed_ref{};
  DigitalSetRefRecord reflex_bank_seed_ref{};
  DigitalSetRefRecord trace_store_seed_ref{};
};

class PrimordialSeedRefsView {
 public:
  explicit PrimordialSeedRefsView(PrimordialSeedRefsRecord record)
      : record_(record) {}

  [[nodiscard]] const PrimordialSeedRefsRecord& record() const {
    return record_;
  }

  [[nodiscard]] std::array<NamedSeedRef, 4> refs() const {
    return {{{SeedRefKind::TimeAxis, record_.time_axis_seed_ref},
             {SeedRefKind::ChamberRegistry,
              record_.chamber_registry_seed_ref},
             {SeedRefKind::ReflexBank, record_.reflex_bank_seed_ref},
             {SeedRefKind::TraceStore, record_.trace_store_seed_ref}}};
  }

  [[nodiscard]] bool only_refs() const {
    for (const auto& named_ref : refs()) {
      if (named_ref.ref.record_id == 0) {
        return false;
      }
    }
    return true;
  }

 private:
  PrimordialSeedRefsRecord record_;
};

inline DigitalSetRefRecord make_seed_ref(std::uint64_t record_id,
                                         RecordTypeTag type_tag,
                                         const std::string& trace_id) {
  DigitalSetRefRecord ref;
  ref.record_id = record_id;
  ref.expected_type_tag = type_tag;
  ref.expected_generation = 1;
  ref.permission_mask = 0;
  ref.trace_id = trace_id;
  return ref;
}

}  // namespace asking_star::v55
