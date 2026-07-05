#include "asking_star/gcyy/trace_sink.hpp"

#include <utility>

namespace asking_star::gcyy {

void TraceSink::record(TraceEvent event) { events_.push_back(std::move(event)); }

const std::vector<TraceEvent>& TraceSink::events() const { return events_; }

std::size_t TraceSink::size() const { return events_.size(); }

}  // namespace asking_star::gcyy

