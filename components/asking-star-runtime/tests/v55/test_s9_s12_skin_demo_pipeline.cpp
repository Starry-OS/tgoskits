#include "asking_star/v55/v55_demo_pipeline.hpp"

#include <cassert>
#include <string>

int main() {
  using asking_star::v55::AdapterMode;
  using asking_star::v55::SkinUIEventRecord;
  using asking_star::v55::SkinUIProjection;
  using asking_star::v55::V55DemoPipeline;
  using asking_star::v55::WalkerInputKind;

  const SkinUIProjection skin;
  const auto ui_input =
      skin.event_to_walker_input(SkinUIEventRecord{1, "click-run", "v55-s9"});
  assert(ui_input.kind == WalkerInputKind::UiEvent);

  const V55DemoPipeline pipeline;
  const auto mock_result =
      pipeline.run(WalkerInputKind::Command, AdapterMode::Mock);
  assert(mock_result.skin_json.find("\"adapter_mode\":\"mock\"") !=
         std::string::npos);
  assert(!mock_result.board_real_claim);
  assert(mock_result.preset_requires_sun_admission);

  const auto replay_result =
      pipeline.run(WalkerInputKind::AiResult, AdapterMode::Replay);
  assert(replay_result.skin_json.find("\"adapter_mode\":\"replay\"") !=
         std::string::npos);
  assert(!replay_result.board_real_claim);

  const auto stable_dryrun =
      pipeline.run(WalkerInputKind::Command, AdapterMode::DryRun);
  assert(stable_dryrun.skin_json.find("\"adapter_mode\":\"dry_run\"") !=
         std::string::npos);
  assert(!stable_dryrun.board_real_claim);
  return 0;
}
