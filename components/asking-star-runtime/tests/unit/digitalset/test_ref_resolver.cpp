#include "asking_star/digitalset/digital_set.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalSet set;
  const auto task =
      set.store.append(asking_star::v5::RecordTypeTag::Task, "task", "t");
  asking_star::v5::RefResolver resolver(set.store);
  const auto result = resolver.resolve(asking_star::v5::make_ref(task.header));
  assert(result.ok);
  assert(result.record->payload == "task");
  return 0;
}

