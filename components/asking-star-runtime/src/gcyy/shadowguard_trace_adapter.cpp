#include "asking_star/gcyy/shadowguard_trace_adapter.hpp"

#include <utility>

namespace asking_star::gcyy {

ShadowGuardTraceAdapter::ShadowGuardTraceAdapter(TraceSink& sink)
    : sink_(sink) {}

void ShadowGuardTraceAdapter::record(std::string trace_id,
                                     std::string event_kind,
                                     std::string message, GcyyStatus status) {
  TraceEvent event;
  event.event_id = "trace-event-" + std::to_string(next_id_++);
  event.trace_id = std::move(trace_id);
  event.event_kind = std::move(event_kind);
  event.status = status;
  event.message = std::move(message);
  sink_.record(std::move(event));
}

}  // namespace asking_star::gcyy
