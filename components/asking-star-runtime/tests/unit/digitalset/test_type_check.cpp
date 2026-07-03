#include "asking_star/digitalset/digital_set.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalSet set;
  const auto record =
      set.store.append(asking_star::v5::RecordTypeTag::Task, "task", "t");
  auto ref = asking_star::v5::make_ref(record.header);
  ref.expected_type_tag = asking_star::v5::RecordTypeTag::DagEdge;
  asking_star::v5::RefResolver resolver(set.store);
  const auto result = resolver.resolve(ref);
  assert(!result.ok);
  assert(result.error == "type_tag_mismatch");
  return 0;
}

