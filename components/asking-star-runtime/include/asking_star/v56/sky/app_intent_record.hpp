#pragma once

#include <string>

namespace asking_star::v56::sky {

enum class RuntimeProfileKind {
  Shell,
  NativeTool,
  Python,
  CppTool,
  RknnDemoWrapper,
  ReplayApp,
  MockApp,
};

struct AppIntentRecord {
  std::string intent_id;
  std::string trace_id;
  RuntimeProfileKind runtime_profile{RuntimeProfileKind::Shell};
  std::string source_kind;
  std::string normalized_payload;
  std::string capability_need;

  [[nodiscard]] bool is_valid() const;
};

[[nodiscard]] const char* to_string(RuntimeProfileKind kind);

}  // namespace asking_star::v56::sky

