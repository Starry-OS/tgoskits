#include "asking_star/v55/algebra_skeleton.hpp"
#include "asking_star/v55/primordial_seed_refs.hpp"

#include <cassert>

int main() {
  using asking_star::v5::RecordTypeTag;
  using asking_star::v55::AlgebraSkeleton;
  using asking_star::v55::JointRefRole;
  using asking_star::v55::MainTimeAxisRecord;
  using asking_star::v55::TimelineJointView;
  using asking_star::v55::make_seed_ref;
  using asking_star::v55::mount_ref;

  MainTimeAxisRecord axis;
  axis.axis_record_id = 100;
  axis.seed_record_id = 10;
  axis.first_tick = 1;
  axis.tick_width = 1;

  AlgebraSkeleton skeleton(axis);
  auto joint = skeleton.make_joint(200, 2);
  mount_ref(joint,
            JointRefRole::WalkerInput,
            make_seed_ref(300, RecordTypeTag::Fragment, "v55-s2"));
  mount_ref(joint,
            JointRefRole::TraceEvent,
            make_seed_ref(301, RecordTypeTag::TraceEvent, "v55-s2"));

  const TimelineJointView view(joint);
  assert(view.only_ref_mounts());
  assert(view.has_role(JointRefRole::WalkerInput));
  assert(view.has_role(JointRefRole::TraceEvent));
  assert(skeleton.axis().joint_ids.size() == 1);
  return 0;
}
