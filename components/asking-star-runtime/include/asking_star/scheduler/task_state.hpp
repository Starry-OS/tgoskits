#pragma once

namespace asking_star::v5 {

enum class TaskState {
  Created,
  Ready,
  Running,
  Waiting,
  Completed,
  Failed,
  RetryPending,
  Cancelled,
  Skipped,
  Merged,
  Archived
};

enum class DagEdgeKind {
  DependsOn,
  Blocks,
  FanOut,
  FanIn,
  Join,
  CancelGroup,
  RetryGroup,
  TraceOnly
};

}  // namespace asking_star::v5

