#include "asking_star/v55/app_gene_charge.hpp"

#include <cassert>

int main() {
  using asking_star::v5::RecordTypeTag;
  using asking_star::v55::AppChargeBuilder;
  using asking_star::v55::AppGeneBuilder;
  using asking_star::v55::WalkerIngress;
  using asking_star::v55::WalkerInputKind;
  using asking_star::v55::WalkerInputRecord;
  using asking_star::v55::make_app_intent;

  WalkerInputRecord input;
  input.input_id = 42;
  input.kind = WalkerInputKind::AiResult;
  input.payload = "detection:ball";
  input.trace_id = "v55-s3-s4";

  const WalkerIngress ingress;
  const auto fragment = ingress.accept(input);
  assert(fragment.header.type_tag == RecordTypeTag::Fragment);
  assert(fragment.records.size() == 1);

  const auto intent = make_app_intent(input);
  const AppGeneBuilder gene_builder;
  const auto app_gene = gene_builder.build(intent, fragment.header.record_id);
  assert(app_gene.app_category == "ai_result");
  assert(app_gene.gene.source_fragment_ref.record_id == fragment.header.record_id);

  const AppChargeBuilder charge_builder;
  const auto app_charge = charge_builder.build(app_gene, 3);
  assert(app_charge.requires_sun_admission);
  assert(app_charge.charge.gene_ref.expected_type_tag == RecordTypeTag::Gene);
  assert(app_charge.charge.ttl_ticks == 3);
  return 0;
}
