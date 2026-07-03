#include "asking_star/gcyy/charge_cache.hpp"

namespace asking_star::gcyy {

void ChargeCache::put(const ChargeView& charge) {
  entries_[charge.origin_gene_id] = charge;
}

std::optional<ChargeView> ChargeCache::find(const std::string& gene_id) {
  auto it = entries_.find(gene_id);
  if (it == entries_.end()) {
    ++misses_;
    return std::nullopt;
  }
  ++hits_;
  return it->second;
}

double ChargeCache::hit_rate() const {
  const auto total = hits_ + misses_;
  return total == 0 ? 0.0 : static_cast<double>(hits_) / total;
}

bool ChargeCache::has_collision(const ChargeView& charge) const {
  auto it = entries_.find(charge.origin_gene_id);
  return it != entries_.end() && it->second.charge_id != charge.charge_id;
}

}  // namespace asking_star::gcyy

