#include "asking_star/gcyy/gene_cache.hpp"

namespace asking_star::gcyy {

void GeneCache::put(const GeneView& gene) { entries_[gene.semantic_hash] = gene; }

std::optional<GeneView> GeneCache::find(const std::string& key) {
  auto it = entries_.find(key);
  if (it == entries_.end()) {
    ++misses_;
    return std::nullopt;
  }
  ++hits_;
  return it->second;
}

double GeneCache::hit_rate() const {
  const auto total = hits_ + misses_;
  return total == 0 ? 0.0 : static_cast<double>(hits_) / total;
}

bool GeneCache::has_collision(const GeneView& gene) const {
  auto it = entries_.find(gene.semantic_hash);
  return it != entries_.end() && it->second.gene_id != gene.gene_id;
}

}  // namespace asking_star::gcyy

