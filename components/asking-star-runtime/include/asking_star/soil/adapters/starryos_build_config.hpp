#pragma once

#include <string>

namespace asking_star::soil::adapters {

enum class StarryOSAdapterMode {
  DryRun,
  HostMock,
  BoardReal,
};

struct StarryOSBuildConfig {
  bool enabled{false};
  StarryOSAdapterMode mode{StarryOSAdapterMode::DryRun};
};

[[nodiscard]] const char* to_string(StarryOSAdapterMode mode);
[[nodiscard]] StarryOSAdapterMode parse_starryos_adapter_mode(
    const std::string& mode);
[[nodiscard]] StarryOSBuildConfig default_starryos_build_config();

}  // namespace asking_star::soil::adapters

