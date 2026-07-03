#pragma once

#include <string>

namespace asking_star::compat {

class TypeNormalizer {
 public:
  [[nodiscard]] std::string normalize_legacy_type(
      const std::string& legacy_type) const;
  [[nodiscard]] std::string normalize_v5_type(const std::string& v5_type) const;
};

}  // namespace asking_star::compat

