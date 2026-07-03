#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace asking_star {

using Timestamp = std::chrono::system_clock::time_point;

inline Timestamp now() {
  return std::chrono::system_clock::now();
}

enum class RuntimeMode {
  AskingStar,
  ShadowGuard,
};

struct RuntimeWeights {
  float yin_weight{0.5F};
  float yang_weight{0.5F};
  float exec_weight{1.0F};
  float observe_weight{0.5F};

  [[nodiscard]] bool is_valid() const {
    return yin_weight >= 0.0F && yang_weight >= 0.0F &&
           exec_weight >= 0.0F && observe_weight >= 0.0F;
  }
};

struct RuntimeTemperature {
  float yin_temperature{0.0F};
  float yang_temperature{0.0F};
  bool absolute_zero{false};
  bool unbounded{false};

  [[nodiscard]] bool is_valid() const {
    if (yin_temperature < 0.0F || yang_temperature < 0.0F) {
      return false;
    }
    return !(absolute_zero && unbounded);
  }

  [[nodiscard]] static RuntimeTemperature absolute_zero_state() {
    return RuntimeTemperature{1.0F, 0.0F, true, false};
  }

  [[nodiscard]] static RuntimeTemperature unbounded_state() {
    return RuntimeTemperature{0.0F, 1.0F, false, true};
  }
};

inline RuntimeWeights weights_for(RuntimeMode mode) {
  switch (mode) {
    case RuntimeMode::ShadowGuard:
      return RuntimeWeights{1.0F, 0.2F, 0.2F, 1.0F};
    case RuntimeMode::AskingStar:
    default:
      return RuntimeWeights{};
  }
}

struct Intent {
  std::string id;
  std::string walker_id;
  std::string description;
  Timestamp created_at{now()};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && !walker_id.empty() && !description.empty();
  }
};

enum class EventType {
  Input,
  IntentCreated,
  YinCommit,
  YangRebuild,
  ModeSwitched,
};

struct Event {
  std::uint64_t sequence{0};
  EventType type{EventType::Input};
  std::string id;
  std::string payload;
  Timestamp occurred_at{now()};

  [[nodiscard]] bool is_valid() const {
    return sequence > 0 && !id.empty();
  }
};

struct StateDiff {
  std::string summary;
  std::vector<std::string> added_keys;
  std::vector<std::string> changed_keys;
  std::vector<std::string> removed_keys;

  [[nodiscard]] bool is_valid() const {
    return !summary.empty() || !added_keys.empty() || !changed_keys.empty() ||
           !removed_keys.empty();
  }
};

struct StateNode {
  std::string id;
  std::vector<std::string> parent_ids;
  StateDiff diff;
  Timestamp created_at{now()};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && diff.is_valid();
  }
};

struct Commit {
  std::string id;
  std::string state_node_id;
  StateDiff compressed_diff;
  Timestamp created_at{now()};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && !state_node_id.empty() && compressed_diff.is_valid();
  }
};

inline const char* to_string(RuntimeMode mode) {
  switch (mode) {
    case RuntimeMode::AskingStar:
      return "asking_star";
    case RuntimeMode::ShadowGuard:
      return "shadow_guard";
  }
  return "asking_star";
}

inline const char* to_string(EventType type) {
  switch (type) {
    case EventType::Input:
      return "input";
    case EventType::IntentCreated:
      return "intent_created";
    case EventType::YinCommit:
      return "yin_commit";
    case EventType::YangRebuild:
      return "yang_rebuild";
    case EventType::ModeSwitched:
      return "mode_switched";
  }
  return "input";
}

}  // namespace asking_star
