#pragma once

#include "asking_star/v55/replay_ai_chamber.hpp"
#include "asking_star/v56/sky/app_intent_record.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v56::sky {

struct AIResultRecord {
  std::uint64_t result_id{0};
  std::string trace_id;
  std::string source_name{"fixture"};
  std::string tensor_hash;
  std::string payload_json;
  bool real_sensor_claim{false};
  bool real_npu_claim{false};
  bool starryos_native_claim{false};
};

struct PouchRuntimeResult {
  AppIntentRecord intent;
  v55::ReplayAiChamberRecord replay;
  bool replay_claim{true};
  bool real_sensor_claim{false};
  bool real_npu_claim{false};
  bool starryos_native_claim{false};

  [[nodiscard]] bool is_valid() const;
};

class PouchRuntime {
 public:
  [[nodiscard]] PouchRuntimeResult accept_ai_result(
      const AIResultRecord& ai_result,
      const v55::ChamberPlacementRecord& placement,
      std::uint64_t logical_order) const;
};

}  // namespace asking_star::v56::sky
