#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace asking_star::walker {

enum class WalkerInputKind {
  Command,
  Event,
  SensorMock,
  ActivityMock,
  TestPayload,
};

struct WalkerInput {
  WalkerInputKind kind{WalkerInputKind::TestPayload};
  std::string source_id;
  std::string trace_id;
  std::string label;
  std::vector<std::byte> payload;
};

struct NormalizedWalkerInput {
  WalkerInputKind kind{WalkerInputKind::TestPayload};
  std::string source_id;
  std::string trace_id;
  std::string star_tag;
  std::string star_pointer;
  std::vector<std::byte> payload;
  std::string payload_hash;
};

[[nodiscard]] const char* to_string(WalkerInputKind kind);

}  // namespace asking_star::walker

