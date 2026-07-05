#pragma once

#include <map>
#include <string>

namespace asking_star::core::charge {

struct ChargePayload {
  std::string semantic_key;
  std::string body;
  std::map<std::string, std::string> metadata;

  [[nodiscard]] bool is_valid() const {
    return !semantic_key.empty() && !body.empty();
  }
};

}  // namespace asking_star::core::charge
