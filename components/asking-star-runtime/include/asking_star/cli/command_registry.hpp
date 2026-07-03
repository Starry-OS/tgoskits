#pragma once

#include "asking_star/cli/command_result.hpp"

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace asking_star::cli {

class CommandRegistry {
 public:
  using Handler = std::function<CommandResult(const std::string& args)>;

  void register_command(std::string name, Handler handler);
  [[nodiscard]] bool has_command(const std::string& name) const;
  [[nodiscard]] CommandResult execute(const std::string& name,
                                      const std::string& args) const;
  [[nodiscard]] std::vector<std::string> list_commands() const;

 private:
  std::map<std::string, Handler> handlers_;
};

}  // namespace asking_star::cli
