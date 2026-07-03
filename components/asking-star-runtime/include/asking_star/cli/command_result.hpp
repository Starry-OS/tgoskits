#pragma once

#include <string>

namespace asking_star::cli {

struct CommandResult {
  bool ok{true};
  std::string message;
  std::string trace_id;
  bool exit_requested{false};
};

}  // namespace asking_star::cli
