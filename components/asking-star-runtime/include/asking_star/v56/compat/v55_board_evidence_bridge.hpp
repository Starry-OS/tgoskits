#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v56::compat {

struct BoardEvidence {
  std::string adapter_mode;
  std::string board_log_ref;
  std::string timestamp;
  std::string marker;
  std::string kernel_request_trace_ref;
  std::string kernel_result_trace_ref;
  std::string latency_or_output_hash;
  std::string binary_sha256;
  std::string commit_hash;
  std::uint64_t latency_ns{0};

  [[nodiscard]] bool has_complete_boardreal_evidence() const;
};

class V55BoardEvidenceBridge {
 public:
  V55BoardEvidenceBridge() = default;
  explicit V55BoardEvidenceBridge(BoardEvidence evidence);

  [[nodiscard]] BoardEvidence current_evidence() const;
  [[nodiscard]] bool is_boardreal_allowed() const;

 private:
  BoardEvidence evidence_;
};

}  // namespace asking_star::v56::compat

