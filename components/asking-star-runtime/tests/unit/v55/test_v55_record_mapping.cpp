#include "asking_star/v55/digitalset_record_mapping.hpp"

#include <cassert>

int main() {
  using asking_star::v55::AdapterMode;
  using asking_star::v55::AppIntentRecord;
  using asking_star::v55::ChamberPlacementRecord;
  using asking_star::v55::ChamberPouchRecord;
  using asking_star::v55::ChamberReflexGeneRecord;
  using asking_star::v55::TimelineJointRecord;
  using asking_star::v55::WalkerInputKind;
  using asking_star::v55::header_for;
  using asking_star::v55::make_v55_ref;
  using asking_star::v55::ref_matches_header;

  AppIntentRecord intent{10, WalkerInputKind::Command, "echo", "v55-q1"};
  const auto intent_header = header_for(intent);
  const auto intent_ref = make_v55_ref(intent_header);
  assert(ref_matches_header(intent_ref, intent_header));

  TimelineJointRecord joint;
  joint.joint_id = 20;
  joint.tick = 1;
  const auto joint_header = header_for(joint, "v55-q1");
  const auto joint_ref = make_v55_ref(joint_header);
  assert(ref_matches_header(joint_ref, joint_header));

  ChamberPlacementRecord placement;
  placement.placement_id = 30;
  placement.adapter_mode = AdapterMode::DryRun;
  const auto placement_header = header_for(placement, "v55-q1");
  const auto placement_ref = make_v55_ref(placement_header);
  assert(ref_matches_header(placement_ref, placement_header));

  ChamberPouchRecord pouch;
  pouch.pouch_id = 40;
  const auto pouch_header = header_for(pouch, "v55-q1");
  auto stale_ref = make_v55_ref(pouch_header);
  stale_ref.expected_generation = pouch_header.generation + 1;
  assert(!ref_matches_header(stale_ref, pouch_header));

  ChamberReflexGeneRecord reflex;
  reflex.reflex_gene_id = 50;
  const auto reflex_header = header_for(reflex, "v55-q1");
  const auto reflex_ref = make_v55_ref(reflex_header);
  assert(ref_matches_header(reflex_ref, reflex_header));
  return 0;
}
