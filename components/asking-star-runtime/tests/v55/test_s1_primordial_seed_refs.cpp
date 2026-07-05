#include "asking_star/v55/primordial_seed_refs.hpp"

#include <cassert>

int main() {
  using asking_star::v5::RecordTypeTag;
  using asking_star::v55::PrimordialSeedRefsRecord;
  using asking_star::v55::PrimordialSeedRefsView;
  using asking_star::v55::make_seed_ref;

  PrimordialSeedRefsRecord record;
  record.time_axis_seed_ref =
      make_seed_ref(10, RecordTypeTag::TimeAxisSeed, "v55-s1");
  record.chamber_registry_seed_ref =
      make_seed_ref(11, RecordTypeTag::Payload, "v55-s1");
  record.reflex_bank_seed_ref =
      make_seed_ref(12, RecordTypeTag::Payload, "v55-s1");
  record.trace_store_seed_ref =
      make_seed_ref(13, RecordTypeTag::TraceEvent, "v55-s1");

  const PrimordialSeedRefsView view(record);
  assert(view.only_refs());
  assert(view.refs()[0].ref.record_id == 10);
  assert(view.refs()[3].ref.expected_type_tag == RecordTypeTag::TraceEvent);
  return 0;
}
