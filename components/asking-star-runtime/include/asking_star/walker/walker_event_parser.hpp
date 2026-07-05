#pragma once

#include "asking_star/walker/walker_input_normalizer.hpp"

#include <string>

namespace asking_star::walker {

// Parses event-like text into WalkerInput. It does not enter GCYY internals.
class WalkerEventParser {
 public:
  [[nodiscard]] WalkerInput parse_event(std::string event_name,
                                        std::string payload,
                                        std::string trace_id) const;
  [[nodiscard]] WalkerInput parse_sensor_mock(std::string sensor_name,
                                              std::string payload,
                                              std::string trace_id) const;
  [[nodiscard]] WalkerInput parse_activity_mock(std::string activity_name,
                                                std::string payload,
                                                std::string trace_id) const;
};

}  // namespace asking_star::walker

