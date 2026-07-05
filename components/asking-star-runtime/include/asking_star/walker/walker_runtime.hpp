#pragma once

#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"
#include "asking_star/walker/walker_command_adapter.hpp"
#include "asking_star/walker/walker_event_parser.hpp"
#include "asking_star/walker/walker_input_normalizer.hpp"

namespace asking_star::walker {

// WalkerRuntime is the only external input adapter for V5.
class WalkerRuntime {
 public:
  [[nodiscard]] asking_star::gcyy::GcyyResult ingest(
      const WalkerInput& input,
      asking_star::gcyy::DigitalSetFragment& out_fragment) const;

  [[nodiscard]] asking_star::gcyy::GcyyResult ingest_command(
      const std::string& command, const std::string& trace_id,
      asking_star::gcyy::DigitalSetFragment& out_fragment) const;

  [[nodiscard]] asking_star::gcyy::GcyyResult ingest_event(
      const std::string& event_name, const std::string& payload,
      const std::string& trace_id,
      asking_star::gcyy::DigitalSetFragment& out_fragment) const;

  [[nodiscard]] asking_star::gcyy::GcyyResult ingest_sensor_mock(
      const std::string& sensor_name, const std::string& payload,
      const std::string& trace_id,
      asking_star::gcyy::DigitalSetFragment& out_fragment) const;

  [[nodiscard]] bool touches_gcyy_internals() const;
  [[nodiscard]] bool touches_scheduler_or_soil() const;

 private:
  WalkerInputNormalizer normalizer_;
  WalkerEventParser parser_;
  WalkerCommandAdapter command_adapter_;
};

}  // namespace asking_star::walker

