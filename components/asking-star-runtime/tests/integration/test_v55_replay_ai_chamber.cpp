#include "asking_star/v55/replay_ai_chamber.hpp"

#include <cassert>
#include <string>

int main() {
  using asking_star::v55::AdapterMode;
  using asking_star::v55::ChamberPlacementRecord;
  using asking_star::v55::ReplayAiChamber;
  using asking_star::v55::ReplayAiResultRecord;

  const ReplayAiResultRecord ai_result{42,
                                       "trace-replay-ai",
                                       "detection.json",
                                       "tensor-sha256-demo",
                                       "{\"label\":\"star\",\"score\":0.99}",
                                       false};
  const ChamberPlacementRecord placement{55, 4, AdapterMode::Replay,
                                         "ai-result-replay", true};

  ReplayAiChamber chamber;
  const auto replay = chamber.replay(ai_result, placement, 9);

  assert(replay.replay_claim);
  assert(!replay.real_sensor_claim);
  assert(replay.execution.adapter_mode == AdapterMode::Replay);
  assert(replay.pouch.health == "healthy");
  assert(replay.pouch.output.find("tensor-sha256-demo") != std::string::npos);
  assert(replay.trace.trace_id == "trace-replay-ai");
  assert(replay.trace.adapter_mode == "Replay");
  assert(replay.trace.logical_order == 9);

  const ReplayAiResultRecord missing_hash{43, "trace-missing", "fixture", "",
                                          "{}", false};
  const auto degraded = chamber.replay(missing_hash, placement, 10);
  assert(degraded.pouch.health == "degraded");
  assert(degraded.pouch.fallback == "missing-tensor-hash");
  assert(!degraded.real_sensor_claim);

  return 0;
}
