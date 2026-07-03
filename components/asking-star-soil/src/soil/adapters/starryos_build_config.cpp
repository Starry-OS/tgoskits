#include "asking_star/soil/adapters/starryos_build_config.hpp"

namespace asking_star::soil::adapters {

const char* to_string(StarryOSAdapterMode mode) {
  switch (mode) {
    case StarryOSAdapterMode::DryRun:
      return "DryRun";
    case StarryOSAdapterMode::HostMock:
      return "HostMock";
    case StarryOSAdapterMode::BoardReal:
      return "BoardReal";
  }
  return "DryRun";
}

StarryOSAdapterMode parse_starryos_adapter_mode(const std::string& mode) {
  if (mode == "HostMock") {
    return StarryOSAdapterMode::HostMock;
  }
  if (mode == "BoardReal") {
    return StarryOSAdapterMode::BoardReal;
  }
  return StarryOSAdapterMode::DryRun;
}

StarryOSBuildConfig default_starryos_build_config() {
#ifdef ASKING_STAR_ENABLE_STARRYOS_ADAPTER_COMPILED
  const bool enabled = ASKING_STAR_ENABLE_STARRYOS_ADAPTER_COMPILED != 0;
#else
  const bool enabled = false;
#endif
#ifdef ASKING_STAR_STARRYOS_ADAPTER_MODE_STRING
  const auto mode =
      parse_starryos_adapter_mode(ASKING_STAR_STARRYOS_ADAPTER_MODE_STRING);
#else
  const auto mode = StarryOSAdapterMode::DryRun;
#endif
  return StarryOSBuildConfig{enabled, mode};
}

}  // namespace asking_star::soil::adapters

