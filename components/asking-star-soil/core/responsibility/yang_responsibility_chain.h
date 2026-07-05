#pragma once

#include "core/responsibility/responsibility_trace.h"

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace asking_star::core::responsibility {

struct YangResponsibilityEvent {
  ResponsibilityTraceId trace_id;
  ResponsibilityStatus status{ResponsibilityStatus::Scheduled};
  std::string owner_id;
  std::string delegate_id;
  std::string result;
  std::string reason;
  asking_star::Timestamp occurred_at{asking_star::now()};

  [[nodiscard]] bool is_valid() const {
    return trace_id.is_valid() && !owner_id.empty() && !reason.empty();
  }
};

class YangResponsibilityChain {
 public:
  void scheduled(ResponsibilityTrace trace) {
    if (!trace.is_valid()) {
      throw std::invalid_argument("invalid scheduled responsibility trace");
    }
    const auto id = trace.id.value;
    traces_[id] = trace;
    events_.push_back({trace.id, ResponsibilityStatus::Scheduled,
                       trace.owner.id, "", trace.result, trace.reason});
  }

  void delegated(const ResponsibilityTraceId& id, const std::string& delegate_id,
                 const std::string& reason) {
    update(id, ResponsibilityStatus::Delegated, delegate_id, "delegated",
           reason);
  }

  void executed(const ResponsibilityTraceId& id, const std::string& result,
                const std::string& reason) {
    update(id, ResponsibilityStatus::Executed, "", result, reason);
  }

  void failed(const ResponsibilityTraceId& id, const std::string& result,
              const std::string& reason) {
    update(id, ResponsibilityStatus::Failed, "", result, reason);
  }

  void feedback_returned(const ResponsibilityTraceId& id,
                         const std::string& result,
                         const std::string& reason) {
    update(id, ResponsibilityStatus::FeedbackReturned, "", result, reason);
  }

  [[nodiscard]] ResponsibilityTrace trace(const ResponsibilityTraceId& id) const {
    auto it = traces_.find(id.value);
    if (it == traces_.end()) {
      throw std::invalid_argument("missing responsibility trace");
    }
    return it->second;
  }

  [[nodiscard]] const std::vector<YangResponsibilityEvent>& events() const {
    return events_;
  }

 private:
  void update(const ResponsibilityTraceId& id, ResponsibilityStatus status,
              const std::string& delegate_id, const std::string& result,
              const std::string& reason) {
    if (!id.is_valid() || result.empty() || reason.empty()) {
      throw std::invalid_argument("invalid responsibility event");
    }
    auto it = traces_.find(id.value);
    if (it == traces_.end()) {
      throw std::invalid_argument("missing responsibility trace");
    }
    it->second.status = status;
    it->second.result = result;
    it->second.reason = reason;
    it->second.updated_at = asking_star::now();
    events_.push_back(
        {id, status, it->second.owner.id, delegate_id, result, reason});
  }

  std::unordered_map<std::string, ResponsibilityTrace> traces_;
  std::vector<YangResponsibilityEvent> events_;
};

}  // namespace asking_star::core::responsibility
