#pragma once

#include "asking_star/gcyy/trace_event.hpp"

#include <vector>

namespace asking_star::gcyy {

class TraceSink {
 public:
  void record(TraceEvent event);
  [[nodiscard]] const std::vector<TraceEvent>& events() const;
  [[nodiscard]] std::size_t size() const;

 private:
  std::vector<TraceEvent> events_;
};

}  // namespace asking_star::gcyy

