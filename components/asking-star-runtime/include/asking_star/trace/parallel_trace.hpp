#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v5 {

struct TraceEventRecord {
  std::string trace_id;
  DigitalSetRefRecord record_ref;
  std::uint64_t sun_tick{0};
  DigitalSetRefRecord policy_brain_ref;
  std::uint64_t timewheel_slot{0};
  std::uint64_t timewheel_angle_units{0};
  std::uint64_t priority_ring{0};
  DigitalSetRefRecord timeline_slice_ref;
  DigitalSetRefRecord task_ref;
  DigitalSetRefRecord dag_edge_ref;
  std::uint64_t algebra_index{0};
  DigitalSetRefRecord scheduler_decision_ref;
  DigitalSetRefRecord cell_ref;
  DigitalSetRefRecord organ_queue_ref;
  DigitalSetRefRecord organ_result_ref;
  DigitalSetRefRecord kernel_request_ref;
  DigitalSetRefRecord kernel_result_ref;
  std::string adapter_mode{"Mock"};
  std::uint64_t logical_order{0};
  std::uint64_t physical_finish_order{0};
  std::string status{"ok"};
  std::uint64_t latency_ns{0};
};

}  // namespace asking_star::v5
