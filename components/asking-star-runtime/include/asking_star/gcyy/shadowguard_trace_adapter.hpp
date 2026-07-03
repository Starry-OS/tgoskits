#pragma once

#include "asking_star/gcyy/trace_sink.hpp"

namespace asking_star::gcyy {

class ShadowGuardTraceAdapter {
 public:
  explicit ShadowGuardTraceAdapter(TraceSink& sink);
  void record(std::string trace_id, std::string event_kind,
              std::string message, GcyyStatus status = GcyyStatus::Ok);

 private:
  TraceSink& sink_;
  std::size_t next_id_{1};
};

}  // namespace asking_star::gcyy

