#pragma once

#include "asking_star/v55/reflex_gene_bank.hpp"

#include <cstdint>
#include <sstream>
#include <string>

namespace asking_star::v55 {

struct SkinUIEventRecord {
  std::uint64_t event_id{0};
  std::string payload;
  std::string trace_id;
};

struct SkinStateProjectionRecord {
  std::uint64_t sun_tick{0};
  std::uint64_t current_joint_id{0};
  std::uint64_t selected_chamber_id{0};
  std::string pouch_health;
  std::string trace_status;
  bool reflex_hit{false};
  AdapterMode adapter_mode{AdapterMode::Mock};
};

class SkinUIProjection {
 public:
  [[nodiscard]] std::string to_json(
      const SkinStateProjectionRecord& state) const {
    std::ostringstream out;
    out << "{";
    out << "\"sun_tick\":" << state.sun_tick << ",";
    out << "\"current_joint_id\":" << state.current_joint_id << ",";
    out << "\"selected_chamber_id\":" << state.selected_chamber_id << ",";
    out << "\"pouch_health\":\"" << state.pouch_health << "\",";
    out << "\"trace_status\":\"" << state.trace_status << "\",";
    out << "\"reflex_hit\":" << (state.reflex_hit ? "true" : "false") << ",";
    out << "\"adapter_mode\":\"" << adapter_mode_name(state.adapter_mode)
        << "\"";
    out << "}";
    return out.str();
  }

  [[nodiscard]] WalkerInputRecord event_to_walker_input(
      const SkinUIEventRecord& event) const {
    WalkerInputRecord input;
    input.input_id = event.event_id;
    input.kind = WalkerInputKind::UiEvent;
    input.payload = event.payload;
    input.trace_id = event.trace_id;
    return input;
  }

 private:
  [[nodiscard]] static const char* adapter_mode_name(AdapterMode mode) {
    switch (mode) {
      case AdapterMode::Host:
        return "host";
      case AdapterMode::Mock:
        return "mock";
      case AdapterMode::Replay:
        return "replay";
      case AdapterMode::DryRun:
        return "dry_run";
      case AdapterMode::HostMock:
        return "host_mock";
      case AdapterMode::BoardReal:
        return "board_real";
    }
    return "unknown";
  }
};

}  // namespace asking_star::v55
