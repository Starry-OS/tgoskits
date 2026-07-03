#pragma once

#include <string>
#include <vector>

namespace asking_star::v56::mainline {

struct FullHostMockDemoReport {
  std::vector<std::string> layer_markers;
  std::string trace_id;
  std::string adapter_mode;
  bool trace_continuous{false};
  bool board_real_claim{false};

  [[nodiscard]] bool is_valid() const;
};

[[nodiscard]] FullHostMockDemoReport run_full_host_mock_demo(
    const std::string& command,
    const std::string& trace_id);

}  // namespace asking_star::v56::mainline
