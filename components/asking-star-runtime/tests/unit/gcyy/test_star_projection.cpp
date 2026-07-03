#include "asking_star/gcyy/mock_yang_operator.hpp"
#include "asking_star/gcyy/mock_yin_operator.hpp"
#include "asking_star/gcyy/star_projection.hpp"

#include <cassert>
#include <cstddef>

int main() {
  asking_star::gcyy::DigitalSetFragment fragment{
      "fragment-1", "walker", "trace-1", "input.text", "star://input/1",
      {std::byte{'x'}}, "hash", "gcyy.fragment.v1"};
  asking_star::gcyy::ProjectionContext context{
      "projection-1", "trace-1", asking_star::gcyy::ProjectionMode::AskingStar,
      "budget-1", "rule-v1", true};
  asking_star::gcyy::MockYinOperator yin;
  asking_star::gcyy::MockYangOperator yang;
  asking_star::gcyy::StarProjection projection(yin, yang);

  asking_star::gcyy::GeneView gene;
  assert(projection.project_to_gene(fragment, context, gene).ok());
  asking_star::gcyy::DigitalCell gene_only;
  assert(projection.make_cell(gene, std::nullopt, context, gene_only).ok());
  assert(!gene_only.has_charge());

  asking_star::gcyy::ChargeView charge;
  assert(projection.project_to_charge(gene, context, charge).ok());
  asking_star::gcyy::DigitalCell charged;
  assert(projection.make_cell(gene, charge, context, charged).ok());
  assert(charged.has_charge());
  assert(charged.state == asking_star::gcyy::DigitalCellState::ChargeReady);
  return 0;
}

