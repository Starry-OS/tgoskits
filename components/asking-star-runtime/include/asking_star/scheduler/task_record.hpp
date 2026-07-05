#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/scheduler/task_state.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v5 {

// TaskRecord is a DigitalSet record. Its relationships must remain RefRecord
// values rather than TaskNode / Edge / Cell raw pointers.
struct TaskRecord {
  std::uint64_t task_id{0};
  std::string name;
  TaskState state{TaskState::Created};
  DigitalSetRefRecord slice_ref;
  DigitalSetRefRecord cell_ref;
  std::vector<DigitalSetRefRecord> edge_refs;
};

struct TaskView {
  TaskRecord record;
};

}  // namespace asking_star::v5
