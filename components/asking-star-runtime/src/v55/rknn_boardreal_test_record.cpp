#include "asking_star/v55/rknn_boardreal_test_record.hpp"

#include <algorithm>
#include <utility>

namespace asking_star::v55 {
namespace {

bool looks_like_sha256(const std::string& value) {
  return value.size() == 64 &&
         std::all_of(value.begin(), value.end(), [](char c) {
           return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
                  (c >= 'A' && c <= 'F');
         });
}

std::string first_hash_after(const std::string& text,
                             const std::string& prefix) {
  const auto start = text.find(prefix);
  if (start == std::string::npos) {
    return {};
  }
  const auto value_start = start + prefix.size();
  const auto value_end = text.find_first_of("\r\n ", value_start);
  return text.substr(value_start, value_end == std::string::npos
                                      ? std::string::npos
                                      : value_end - value_start);
}

}  // namespace

bool RknnBoardHalSmokeRecord::board_hal_path_passed() const {
  return npu_probe_ok && rknpu_registered && npu_hal_smoke_pass &&
         graph_runner_hal_smoke_pass && !cpu_fallback &&
         real_npu_output_buffer && !output_hash_fnv1a64.empty();
}

bool RknnBoardHalSmokeRecord::full_rknn_graph_claim_allowed() const {
  return false;
}

bool UserTaskMarkerRecord::minimum_scheduler_passed() const {
  return runqueue_selected_user && task_context_switch_called;
}

bool UserTaskMarkerRecord::el0_syscall_path_passed() const {
  return user_closure_entered && syscall_entered && write_syscall_entered;
}

bool BoardArtifactGateRecord::host_gate_passed() const {
  return !artifact_name.empty() && looks_like_sha256(sha256) &&
         looks_like_sha256(elf_sha256) &&
         build_profile == "rk3588-user-min-runner-build" &&
         first_load_paddr == "0x40200000" && start_delta == "0x250";
}

RknnBoardHalSmokeRecord RknnBoardrealTestRecordParser::parse_hal_smoke(
    const std::string& uart_log) const {
  RknnBoardHalSmokeRecord record;
  record.npu_probe_ok = has_token(uart_log, "[NPU PROBE] probe_all returned ok");
  record.rknpu_registered = has_token(uart_log, "[NPU PROBE] rknpu registered");
  record.npu_hal_smoke_pass =
      has_token(uart_log, "[NPU SMOKE] final_status=pass") ||
      has_token(uart_log, "npu_hal_smoke_result=true");
  record.graph_runner_hal_smoke_pass =
      has_token(uart_log, "[AI] final_status=graph_runner_hal_smoke_pass") ||
      has_token(uart_log, "rknn_graph_runner_hal_result=true");
  record.cpu_fallback = !has_token(uart_log, "[AI] cpu_fallback=false");
  record.real_npu_output_buffer =
      has_token(uart_log, "board_output_buffer=true") ||
      has_token(uart_log, "[AI] graph_runner_output_bytes=2048");
  record.output_hash_fnv1a64 =
      first_hash_after(uart_log, "output_hash_fnv1a64=");
  if (record.output_hash_fnv1a64.empty()) {
    record.output_hash_fnv1a64 =
        first_hash_after(uart_log, "graph_runner_output_hash_fnv1a64=");
  }
  return record;
}

UserTaskMarkerRecord RknnBoardrealTestRecordParser::parse_user_task_markers(
    const std::string& uart_log) const {
  UserTaskMarkerRecord record;
  auto user_start = uart_log.find("RSU");
  if (user_start == std::string::npos) {
    user_start = uart_log.find("RSRU");
  }
  record.runqueue_selected_user = user_start != std::string::npos;
  const auto user_log =
      record.runqueue_selected_user ? uart_log.substr(user_start) : uart_log;

  record.task_context_switch_called =
      has_token(user_log, "RC") || has_token(user_log, "XY");
  record.task_entry_entered = has_token(user_log, "K0");
  record.user_closure_entered = has_token(user_log, "T0");
  record.context_restore_before_ret = has_token(user_log, "Z");
  record.syscall_entered = has_token(user_log, "TS") || has_token(user_log, "S0");
  record.write_syscall_entered =
      has_token(user_log, "SW") || has_token(user_log, "TW");

  if (record.el0_syscall_path_passed()) {
    record.blocked_after = "syscall-write";
    record.next_probe = "compare-user-output";
  } else if (record.context_restore_before_ret && !record.task_entry_entered) {
    record.blocked_after = "context-switch-ret";
    record.next_probe = "task-entry-prologue";
  } else if (record.runqueue_selected_user &&
             record.task_context_switch_called &&
             !record.task_entry_entered) {
    record.blocked_after = "RSU_RC";
    record.next_probe = "TaskContext::init-or-context_switch";
  } else if (record.task_entry_entered && !record.user_closure_entered) {
    record.blocked_after = "K0_before_T0";
    record.next_probe = "task_entry-current-entry-take";
  } else {
    record.blocked_after = "unknown";
    record.next_probe = "collect-runqueue-marker";
  }
  return record;
}

BoardArtifactGateRecord RknnBoardrealTestRecordParser::make_artifact_gate(
    std::string artifact_name,
    std::string sha256,
    std::string elf_sha256,
    std::string build_profile,
    std::string first_load_paddr,
    std::string start_delta,
    bool kernel_only) const {
  BoardArtifactGateRecord record;
  record.artifact_name = std::move(artifact_name);
  record.sha256 = std::move(sha256);
  record.elf_sha256 = std::move(elf_sha256);
  record.build_profile = std::move(build_profile);
  record.first_load_paddr = std::move(first_load_paddr);
  record.start_delta = std::move(start_delta);
  record.kernel_only = kernel_only;
  return record;
}

bool RknnBoardrealTestRecordParser::has_token(const std::string& text,
                                              const std::string& token) {
  return text.find(token) != std::string::npos;
}

}  // namespace asking_star::v55
