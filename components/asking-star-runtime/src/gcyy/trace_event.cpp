#include "asking_star/gcyy/trace_event.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool TraceEvent::is_valid() const {
  return !event_id.empty() && !trace_id.empty() && !event_kind.empty();
}

std::string TraceEvent::debug_dump() const {
  std::ostringstream out;
  out << "TraceEvent{id=" << event_id << ", trace=" << trace_id
      << ", kind=" << event_kind << ", status=" << to_string(status)
      << ", message=" << message << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

