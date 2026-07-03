#pragma once

#include "asking_star/v56/soil/soil_dual_chamber.hpp"

#include <string>

namespace asking_star::v56::policy {

struct RuntimeProfileRecord {
  std::string profile_id;
  std::string runtime_name;
  bool may_touch_os_boundary{false};
  bool valid{false};
};

struct OSProfileRecord {
  std::string profile_id;
  soil::OSProfileKind kind{soil::OSProfileKind::Mock};
  bool requires_board_evidence{false};
  bool starryos_native_claim{false};
  bool valid{false};
};

struct PlacementDecisionRecord {
  RuntimeProfileRecord runtime;
  OSProfileRecord os;
  bool allowed{false};
  bool board_real_claim{false};
  std::string reason;
};

class ProfileRegistry {
 public:
  [[nodiscard]] RuntimeProfileRecord runtime_profile(
      const std::string& profile_id) const;
  [[nodiscard]] OSProfileRecord os_profile(const std::string& profile_id) const;
};

class PlacementPolicy {
 public:
  [[nodiscard]] PlacementDecisionRecord decide(
      const RuntimeProfileRecord& runtime,
      const OSProfileRecord& os,
      bool has_board_evidence) const;
};

}  // namespace asking_star::v56::policy
