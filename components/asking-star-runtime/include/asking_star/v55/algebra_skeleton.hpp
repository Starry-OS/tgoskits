#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v55 {

using v5::DigitalSetRefRecord;

enum class JointRefRole {
  WalkerInput,
  AppIntent,
  AppGene,
  AppCharge,
  DigitalCell,
  ChamberPlacement,
  SelectedChamber,
  ChamberPouch,
  OrganDispatch,
  SoilRequest,
  KernelResult,
  TraceEvent,
  ReflexCandidate,
};

struct JointRefRecord {
  JointRefRole role{JointRefRole::WalkerInput};
  DigitalSetRefRecord ref{};
};

struct TimelineJointRecord {
  std::uint64_t joint_id{0};
  std::uint64_t tick{0};
  std::uint64_t axis_record_id{0};
  std::vector<JointRefRecord> refs;
};

class TimelineJointView {
 public:
  explicit TimelineJointView(TimelineJointRecord record) : record_(record) {}

  [[nodiscard]] const TimelineJointRecord& record() const {
    return record_;
  }

  [[nodiscard]] bool has_role(JointRefRole role) const {
    for (const auto& item : record_.refs) {
      if (item.role == role && item.ref.record_id != 0) {
        return true;
      }
    }
    return false;
  }

  [[nodiscard]] bool only_ref_mounts() const {
    for (const auto& item : record_.refs) {
      if (item.ref.record_id == 0) {
        return false;
      }
    }
    return true;
  }

 private:
  TimelineJointRecord record_;
};

struct MainTimeAxisRecord {
  std::uint64_t axis_record_id{0};
  std::uint64_t seed_record_id{0};
  std::uint64_t first_tick{0};
  std::uint64_t tick_width{1};
  std::vector<std::uint64_t> joint_ids;
};

class AlgebraSkeleton {
 public:
  explicit AlgebraSkeleton(MainTimeAxisRecord axis) : axis_(axis) {}

  [[nodiscard]] const MainTimeAxisRecord& axis() const {
    return axis_;
  }

  [[nodiscard]] TimelineJointRecord make_joint(std::uint64_t joint_id,
                                               std::uint64_t tick) {
    axis_.joint_ids.push_back(joint_id);
    TimelineJointRecord joint;
    joint.joint_id = joint_id;
    joint.tick = tick;
    joint.axis_record_id = axis_.axis_record_id;
    return joint;
  }

 private:
  MainTimeAxisRecord axis_;
};

inline void mount_ref(TimelineJointRecord& joint,
                      JointRefRole role,
                      const DigitalSetRefRecord& ref) {
  joint.refs.push_back(JointRefRecord{role, ref});
}

}  // namespace asking_star::v55
