#pragma once

#include "asking_star/walker/walker_input_normalizer.hpp"

#include <string>

namespace asking_star::walker {

// Converts command text into WalkerInput; it does not schedule or execute.
class WalkerCommandAdapter {
 public:
  [[nodiscard]] WalkerInput from_command(std::string command,
                                         std::string trace_id) const;
  [[nodiscard]] WalkerInput from_test_payload(std::string label,
                                              std::string payload,
                                              std::string trace_id) const;
};

}  // namespace asking_star::walker

