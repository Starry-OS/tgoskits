#include "asking_star/gcyy/charge_cache.hpp"
#include "asking_star/gcyy/gene_cache.hpp"

#include <cassert>

int main() {
  asking_star::gcyy::GeneView gene;
  gene.gene_id = "gene-1";
  gene.trace_id = "trace-1";
  gene.state_hash = "state";
  gene.semantic_hash = "semantic";
  asking_star::gcyy::GeneCache gene_cache;
  assert(!gene_cache.find(gene.semantic_hash).has_value());
  gene_cache.put(gene);
  assert(gene_cache.find(gene.semantic_hash).has_value());
  assert(gene_cache.hit_rate() > 0.0);

  asking_star::gcyy::ChargeView charge;
  charge.charge_id = "charge-1";
  charge.origin_gene_id = "gene-1";
  charge.trace_id = "trace-1";
  charge.capability_kind = "mock.execute";
  asking_star::gcyy::ChargeCache charge_cache;
  charge_cache.put(charge);
  assert(charge_cache.find("gene-1").has_value());
  assert(!charge_cache.has_collision(charge));
  return 0;
}

