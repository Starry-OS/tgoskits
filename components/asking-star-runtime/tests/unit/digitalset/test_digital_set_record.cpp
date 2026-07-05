#include "asking_star/digitalset/digital_set.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalSet set;
  const auto record = set.store.append(
      asking_star::v5::RecordTypeTag::Payload, "payload", "trace-1");
  assert(record.header.record_id == 1);
  assert(record.header.type_tag == asking_star::v5::RecordTypeTag::Payload);
  assert(record.header.version == 1);
  assert(record.header.generation == 1);
  assert(!record.header.trace_id.empty());
  return 0;
}

