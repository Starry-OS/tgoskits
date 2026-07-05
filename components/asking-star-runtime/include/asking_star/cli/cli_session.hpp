#pragma once

#include "asking_star/cli/command_registry.hpp"
#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/soil/adapters/starryos_build_config.hpp"
#include "asking_star/soil/soil_execution_status.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace asking_star::cli {

struct CliSessionSnapshot {
  std::string session_id{"cli-session-v5"};
  std::string last_trace_id;
  std::string last_fragment_id;
  std::string last_gene_id;
  std::string last_charge_id;
  std::string last_cell_id;
  std::string last_kernel_request_id;
  std::string last_result_status;
  std::string adapter_mode{"DryRun"};
  std::uint64_t end_to_end_latency_ns{0};
};

class CliSession {
 public:
  explicit CliSession(asking_star::soil::adapters::StarryOSAdapterMode mode =
                          asking_star::soil::adapters::StarryOSAdapterMode::
                              DryRun);
  CliSession(const CliSession& other);
  CliSession& operator=(const CliSession& other);
  CliSession(CliSession&& other) noexcept;
  CliSession& operator=(CliSession&& other) noexcept;

  [[nodiscard]] CommandResult execute_command(const std::string& line);
  [[nodiscard]] const CliSessionSnapshot& snapshot() const;
  [[nodiscard]] bool walker_was_used() const;

 private:
  [[nodiscard]] CommandResult execute_runtime_command(
      const std::string& walker_command,
      const std::string& result_text);
  [[nodiscard]] CommandResult status() const;
  [[nodiscard]] CommandResult cell_dump() const;
  [[nodiscard]] CommandResult trace_last() const;
  [[nodiscard]] CommandResult soil_status() const;
  [[nodiscard]] CommandResult adapter_status() const;
  [[nodiscard]] CommandResult ai_status() const;
  [[nodiscard]] CommandResult ai_infer(const std::string& text);
  [[nodiscard]] CommandResult unknown_command(const std::string& command) const;

  void register_commands();
  void copy_state_from(const CliSession& other);
  [[nodiscard]] std::string next_trace_id();

  asking_star::soil::adapters::StarryOSAdapterMode adapter_mode_;
  CommandRegistry registry_;
  CliSessionSnapshot snapshot_;
  std::optional<asking_star::gcyy::DigitalCell> last_cell_;
  bool walker_used_{false};
  std::uint64_t next_trace_index_{1};
};

}  // namespace asking_star::cli
