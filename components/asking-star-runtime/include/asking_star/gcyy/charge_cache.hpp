#pragma once

#include "asking_star/gcyy/charge_view.hpp"

#include <optional>
#include <string>
#include <unordered_map>

namespace asking_star::gcyy {

// In-memory ChargeView cache keyed by origin Gene id.
class ChargeCache {
 public:
  void put(const ChargeView& charge);
  [[nodiscard]] std::optional<ChargeView> find(const std::string& gene_id);
  [[nodiscard]] double hit_rate() const;
  [[nodiscard]] bool has_collision(const ChargeView& charge) const;

 private:
  std::unordered_map<std::string, ChargeView> entries_;
  std::size_t hits_{0};
  std::size_t misses_{0};
};

}  // namespace asking_star::gcyy

