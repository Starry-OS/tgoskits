#pragma once

#include "asking_star/gcyy/trace_event.hpp"
#include "asking_star/gcyy/trace_sink.hpp"

#include <cstddef>
#include <vector>

namespace asking_star::v56::compat {

class V55TraceBridge {
 public:
  V55TraceBridge();
  explicit V55TraceBridge(gcyy::TraceSink& sink);

  void emit(const gcyy::TraceEvent& event);
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] const std::vector<gcyy::TraceEvent>& events() const;

 private:
  gcyy::TraceSink owned_sink_;
  gcyy::TraceSink* sink_{nullptr};
};

}  // namespace asking_star::v56::compat

