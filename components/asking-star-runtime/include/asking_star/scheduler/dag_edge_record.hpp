#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/scheduler/task_state.hpp"

#include <cstdint>

namespace asking_star::v5 {

// DagEdgeRecord is a DigitalSet record connecting TaskRecord refs.
struct DagEdgeRecord {
  std::uint64_t edge_id{0};
  DagEdgeKind kind{DagEdgeKind::DependsOn};
  DigitalSetRefRecord from_task_ref;
  DigitalSetRefRecord to_task_ref;
};

struct DagEdgeView {
  DagEdgeRecord record;
};

}  // namespace asking_star::v5
