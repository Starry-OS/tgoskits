#include "asking_star/scheduler/task_graph_view.hpp"

#include <functional>
#include <unordered_set>

namespace asking_star::v5 {

bool TaskGraphView::has_cycle() const {
  std::unordered_map<std::uint64_t, std::vector<std::uint64_t>> adjacency;
  for (const auto& edge : edges) {
    adjacency[edge.from_task_ref.record_id].push_back(edge.to_task_ref.record_id);
  }

  std::unordered_set<std::uint64_t> visiting;
  std::unordered_set<std::uint64_t> visited;
  std::function<bool(std::uint64_t)> dfs = [&](std::uint64_t id) {
    if (visiting.contains(id)) {
      return true;
    }
    if (visited.contains(id)) {
      return false;
    }
    visiting.insert(id);
    for (const auto next : adjacency[id]) {
      if (dfs(next)) {
        return true;
      }
    }
    visiting.erase(id);
    visited.insert(id);
    return false;
  };

  for (const auto& task : tasks) {
    if (dfs(task.task_id)) {
      return true;
    }
  }
  return false;
}

std::vector<std::uint64_t> TaskGraphView::ready_task_ids() const {
  std::unordered_set<std::uint64_t> blocked;
  for (const auto& edge : edges) {
    blocked.insert(edge.to_task_ref.record_id);
  }
  std::vector<std::uint64_t> ready;
  for (const auto& task : tasks) {
    if (task.state == TaskState::Created && !blocked.contains(task.task_id)) {
      ready.push_back(task.task_id);
    }
  }
  return ready;
}

}  // namespace asking_star::v5
