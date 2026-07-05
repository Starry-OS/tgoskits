#include "asking_star/gcyy/mock_yang_operator.hpp"
#include "asking_star/gcyy/mock_yin_operator.hpp"

#include <cassert>
#include <cstddef>

namespace {

asking_star::gcyy::DigitalSetFragment make_fragment() {
  return asking_star::gcyy::DigitalSetFragment{
      "fragment-1",
      "walker",
      "trace-1",
      "input.text",
      "star://input/1",
      {std::byte{'h'}, std::byte{'i'}},
      "hash",
      "gcyy.fragment.v1"};
}

asking_star::gcyy::ProjectionContext make_context() {
  return asking_star::gcyy::ProjectionContext{
      "projection-1", "trace-1", asking_star::gcyy::ProjectionMode::AskingStar,
      "budget-1", "rule-v1", true};
}

}  // namespace

int main() {
  asking_star::gcyy::MockYinOperator yin;
  asking_star::gcyy::MockYangOperator yang;
  auto fragment = make_fragment();
  auto context = make_context();

  asking_star::gcyy::GeneView first_gene;
  asking_star::gcyy::GeneView second_gene;
  assert(yin.compress(fragment, context, first_gene).ok());
  assert(yin.compress(fragment, context, second_gene).ok());
  assert(first_gene.semantic_hash == second_gene.semantic_hash);

  asking_star::gcyy::ChargeView charge;
  assert(yang.expand(first_gene, context, charge).ok());
  assert(charge.origin_gene_id == first_gene.gene_id);
  assert(charge.trace_id == first_gene.trace_id);

  fragment.payload.clear();
  asking_star::gcyy::GeneView failed_gene;
  auto failed = yin.compress(fragment, context, failed_gene);
  assert(!failed.ok());
  assert(failed.status == asking_star::gcyy::GcyyStatus::MissingPayload);

  return 0;
}

