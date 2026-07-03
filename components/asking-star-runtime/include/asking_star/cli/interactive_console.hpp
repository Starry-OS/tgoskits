#pragma once

#include "asking_star/cli/cli_session.hpp"

#include <istream>
#include <ostream>
#include <string>

namespace asking_star::cli {

class InteractiveConsole {
 public:
  InteractiveConsole(std::istream& input, std::ostream& output,
                     CliSession session = CliSession{});

  void start();
  void stop();
  [[nodiscard]] std::string read_line();
  [[nodiscard]] CommandResult execute_command(const std::string& line);
  void print_prompt();
  void print_logo();

 private:
  std::istream& input_;
  std::ostream& output_;
  CliSession session_;
  bool running_{false};
};

}  // namespace asking_star::cli
