#pragma once

#include "asking_star/v55/app_gene_charge.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v55 {

enum class ChamberKind {
  LinuxRknnRuntime,
  StableStarry,
  DynamicCompat,
  Replay,
  Mock,
  LinuxExternalService,
};

enum class AdapterMode {
  Host,
  Mock,
  Replay,
  DryRun,
  HostMock,
  BoardReal,
};

struct ChamberProfileRecord {
  std::uint64_t chamber_id{0};
  ChamberKind kind{ChamberKind::Mock};
  AdapterMode adapter_mode{AdapterMode::Mock};
  std::string capability;
  std::uint32_t risk_level{0};
};

struct ChamberPlacementRecord {
  std::uint64_t placement_id{0};
  std::uint64_t selected_chamber_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  std::string reason;
  bool requires_sun_admission{true};
};

class ChamberPlacementPolicy {
 public:
  [[nodiscard]] ChamberPlacementRecord select(
      const AppGeneRecord& app_gene,
      const AppChargeRecord& app_charge,
      const std::vector<ChamberProfileRecord>& chambers) const {
    (void)app_charge;
    for (const auto& chamber : chambers) {
      if (matches(app_gene.app_category, chamber)) {
        return make_record(app_gene.gene.gene_id + 3000,
                           chamber,
                           "category-match");
      }
    }
    for (const auto& chamber : chambers) {
      if (chamber.kind == ChamberKind::Mock) {
        return make_record(app_gene.gene.gene_id + 3000,
                           chamber,
                           "fallback-mock");
      }
    }
    return {};
  }

 private:
  [[nodiscard]] static bool matches(const std::string& category,
                                    const ChamberProfileRecord& chamber) {
    if (chamber.kind == ChamberKind::LinuxRknnRuntime) {
      return category == "rknn" || category == "ai_result";
    }
    if (chamber.kind == ChamberKind::StableStarry &&
        chamber.adapter_mode == AdapterMode::DryRun) {
      return true;
    }
    if (category == "replay") {
      return chamber.kind == ChamberKind::Replay;
    }
    if (category == "ai_result") {
      return chamber.kind == ChamberKind::Replay ||
             chamber.kind == ChamberKind::Mock;
    }
    if (category == "external_app") {
      return chamber.kind == ChamberKind::LinuxExternalService;
    }
    return chamber.kind == ChamberKind::Mock;
  }

  [[nodiscard]] static ChamberPlacementRecord make_record(
      std::uint64_t placement_id,
      const ChamberProfileRecord& chamber,
      const std::string& reason) {
    ChamberPlacementRecord placement;
    placement.placement_id = placement_id;
    placement.selected_chamber_id = chamber.chamber_id;
    placement.adapter_mode = chamber.adapter_mode;
    placement.reason = reason;
    placement.requires_sun_admission = true;
    return placement;
  }
};

inline std::vector<ChamberProfileRecord> default_chamber_profiles() {
  return {
      {1, ChamberKind::LinuxRknnRuntime, AdapterMode::Host,
       "librknnrt.so/toolchain-probe", 2},
      {2, ChamberKind::StableStarry, AdapterMode::DryRun, "starryos.console", 1},
      {3, ChamberKind::Replay, AdapterMode::Replay, "ai-result-replay", 1},
      {4, ChamberKind::Mock, AdapterMode::Mock, "mock-fallback", 0},
      {5, ChamberKind::LinuxExternalService, AdapterMode::HostMock,
       "linux-external-service", 1},
  };
}

inline bool adapter_mode_can_claim_board_real(AdapterMode mode) {
  return mode == AdapterMode::BoardReal;
}

}  // namespace asking_star::v55
