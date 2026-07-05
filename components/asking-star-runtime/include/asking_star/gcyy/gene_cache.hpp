#pragma once

#include "asking_star/gcyy/gene_view.hpp"

#include <optional>
#include <string>
#include <unordered_map>

namespace asking_star::gcyy {

// In-memory GeneView cache keyed by deterministic Gene hash.
class GeneCache {
 public:
  void put(const GeneView& gene);
  [[nodiscard]] std::optional<GeneView> find(const std::string& key);
  [[nodiscard]] double hit_rate() const;
  [[nodiscard]] bool has_collision(const GeneView& gene) const;

 private:
  std::unordered_map<std::string, GeneView> entries_;
  std::size_t hits_{0};
  std::size_t misses_{0};
};

}  // namespace asking_star::gcyy

