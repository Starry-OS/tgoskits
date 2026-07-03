#pragma once

#include <string>
#include <vector>

namespace asking_star::core::boot {

struct ShellProbeResult {
  bool stable{false};
  std::vector<std::string> passed_commands;
  std::vector<std::string> failed_commands;

  [[nodiscard]] bool is_valid() const {
    return stable ? !passed_commands.empty() : true;
  }
};

class ShellStabilityProbe {
 public:
  [[nodiscard]] ShellProbeResult evaluate(
      const std::vector<std::string>& command_outputs) const {
    ShellProbeResult result;
    for (const auto& output : command_outputs) {
      if (output.find("blocked:") != std::string::npos ||
          output.find("terminal error:") != std::string::npos ||
          output.empty()) {
        result.failed_commands.push_back(output.empty() ? "<empty>" : output);
      } else {
        result.passed_commands.push_back(output);
      }
    }
    result.stable = !result.passed_commands.empty() &&
                    result.failed_commands.empty();
    return result;
  }
};

}  // namespace asking_star::core::boot
