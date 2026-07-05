#pragma once

#include <string>
#include <vector>

namespace asking_star::v56::testing {

struct LayeredTestStage {
  std::string stage_id;
  std::string layer;
  std::string target_name;
  bool can_run_independently{false};
  bool board_real_allowed{false};

  [[nodiscard]] bool is_valid() const;
};

class LayeredTestMatrix {
 public:
  [[nodiscard]] std::vector<LayeredTestStage> stages() const;
  [[nodiscard]] bool is_complete() const;
};

}  // namespace asking_star::v56::testing
