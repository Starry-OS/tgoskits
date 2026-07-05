#pragma once

#include "asking_star/scheduler/dag_edge_record.hpp"
#include "asking_star/scheduler/task_record.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace asking_star::v5 {

// TaskGraphView is a C++ decoded view over TaskRecord / DagEdgeRecord refs.
// It is not an independent object graph.
struct TaskGraphView {
  std::vector<TaskRecord> tasks;
  std::vector<DagEdgeRecord> edges;

  bool has_cycle() const;
  std::vector<std::uint64_t> ready_task_ids() const;
};

}  // namespace asking_star::v5
