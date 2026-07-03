#pragma once

#include "common_types.h"
#include "core/responsibility/responsibility_owner.h"
#include "core/responsibility/responsibility_requirement.h"
#include "core/responsibility/responsibility_trace_id.h"

#include <string>

namespace asking_star::core::responsibility {

enum class ResponsibilityStatus {
  Scheduled,
  Delegated,
  Executed,
  Failed,
  FeedbackReturned,
};

struct ResponsibilityTrace {
  ResponsibilityTraceId id;
  std::string scheduler_pulse;
  ResponsibilityOwner owner;
  ResponsibilityRequirement requirement;
  std::string action;
  ResponsibilityStatus status{ResponsibilityStatus::Scheduled};
  std::string result;
  std::string reason;
  asking_star::Timestamp opened_at{asking_star::now()};
  asking_star::Timestamp updated_at{asking_star::now()};

  [[nodiscard]] bool is_valid() const {
    return id.is_valid() && !scheduler_pulse.empty() && owner.is_valid() &&
           requirement.is_valid() && !action.empty() && !reason.empty();
  }
};

inline const char* to_string(ResponsibilityStatus status) {
  switch (status) {
    case ResponsibilityStatus::Scheduled:
      return "scheduled";
    case ResponsibilityStatus::Delegated:
      return "delegated";
    case ResponsibilityStatus::Executed:
      return "executed";
    case ResponsibilityStatus::Failed:
      return "failed";
    case ResponsibilityStatus::FeedbackReturned:
      return "feedback_returned";
  }
  return "scheduled";
}

}  // namespace asking_star::core::responsibility
