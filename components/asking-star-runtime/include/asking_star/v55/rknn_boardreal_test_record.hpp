#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace asking_star::v55 {

struct RknnBoardHalSmokeRecord {
  bool npu_probe_ok{false};
  bool rknpu_registered{false};
  bool npu_hal_smoke_pass{false};
  bool graph_runner_hal_smoke_pass{false};
  bool cpu_fallback{true};
  bool real_npu_output_buffer{false};
  std::string output_hash_fnv1a64;

  [[nodiscard]] bool board_hal_path_passed() const;
  [[nodiscard]] bool full_rknn_graph_claim_allowed() const;
};

struct UserTaskMarkerRecord {
  bool runqueue_selected_user{false};
  bool task_context_switch_called{false};
  bool task_entry_entered{false};
  bool user_closure_entered{false};
  bool context_restore_before_ret{false};
  bool syscall_entered{false};
  bool write_syscall_entered{false};
  std::string blocked_after;
  std::string next_probe;

  [[nodiscard]] bool minimum_scheduler_passed() const;
  [[nodiscard]] bool el0_syscall_path_passed() const;
};

struct BoardArtifactGateRecord {
  std::string artifact_name;
  std::string sha256;
  std::string elf_sha256;
  std::string build_profile;
  std::string first_load_paddr;
  std::string start_delta;
  bool kernel_only{false};

  [[nodiscard]] bool host_gate_passed() const;
};

class RknnBoardrealTestRecordParser {
 public:
  [[nodiscard]] RknnBoardHalSmokeRecord parse_hal_smoke(
      const std::string& uart_log) const;

  [[nodiscard]] UserTaskMarkerRecord parse_user_task_markers(
      const std::string& uart_log) const;

  [[nodiscard]] BoardArtifactGateRecord make_artifact_gate(
      std::string artifact_name,
      std::string sha256,
      std::string elf_sha256,
      std::string build_profile,
      std::string first_load_paddr,
      std::string start_delta,
      bool kernel_only) const;

 private:
  [[nodiscard]] static bool has_token(const std::string& text,
                                      const std::string& token);
};

}  // namespace asking_star::v55
