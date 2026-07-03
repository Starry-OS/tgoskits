#pragma once

#include "asking_star/compat/compatibility_view.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace asking_star::compat {

class MappingRegistry {
 public:
  void register_mapping(CompatibilityView view);
  [[nodiscard]] std::optional<CompatibilityView> find(
      const std::string& legacy_type) const;
  [[nodiscard]] std::vector<CompatibilityView> all() const;

 private:
  std::unordered_map<std::string, CompatibilityView> mappings_;
};

[[nodiscard]] MappingRegistry make_default_mapping_registry(
    const std::string& trace_id);

}  // namespace asking_star::compat

