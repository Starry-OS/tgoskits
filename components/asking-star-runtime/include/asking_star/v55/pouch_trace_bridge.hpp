#pragma once

#include "asking_star/trace/parallel_trace.hpp"
#include "asking_star/v55/chamber_starryos_dryrun_bridge.hpp"
#include "asking_star/v55/digitalset_record_mapping.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

[[nodiscard]] inline std::string to_trace_adapter_mode(AdapterMode mode) {
  switch (mode) {
    case AdapterMode::DryRun:
      return "DryRun";
    case AdapterMode::HostMock:
      return "HostMock";
    case AdapterMode::BoardReal:
      return "BoardReal";
    case AdapterMode::Host:
      return "Host";
    case AdapterMode::Replay:
      return "Replay";
    case AdapterMode::Mock:
    default:
      return "Mock";
  }
}

struct PouchTraceBridgeRecord {
  asking_star::v5::TraceEventRecord event;
  bool trace_complete{false};
  bool board_real_claim{false};
};

class PouchTraceBridge {
 public:
  [[nodiscard]] PouchTraceBridgeRecord record(
      const ChamberExecutionRecord& execution,
      const ChamberPouchRecord& pouch,
      const StarryOSDryRunBridgeRecord& starryos,
      std::uint64_t logical_order) const {
    PouchTraceBridgeRecord out;
    out.event.trace_id = starryos.request.trace_id;
    out.event.record_ref =
        make_v55_ref(make_v55_header(execution.execution_id,
                                     RecordTypeTag::TraceEvent,
                                     out.event.trace_id));
    out.event.timeline_slice_ref =
        make_v55_ref(make_v55_header(execution.placement_id,
                                     RecordTypeTag::TimelineSlice,
                                     out.event.trace_id));
    out.event.task_ref = out.event.record_ref;
    out.event.cell_ref =
        make_v55_ref(make_v55_header(execution.placement_id,
                                     RecordTypeTag::DigitalCell,
                                     out.event.trace_id));
    out.event.kernel_request_ref =
        make_v55_ref(make_v55_header(execution.execution_id + 5000,
                                     RecordTypeTag::KernelRequest,
                                     out.event.trace_id));
    out.event.kernel_result_ref =
        make_v55_ref(make_v55_header(execution.execution_id + 6000,
                                     RecordTypeTag::KernelResult,
                                     out.event.trace_id));
    out.event.organ_result_ref = make_v55_ref(header_for(pouch, out.event.trace_id));
    out.event.adapter_mode = to_trace_adapter_mode(execution.adapter_mode);
    out.event.logical_order = logical_order;
    out.event.physical_finish_order = logical_order;
    out.event.status = starryos.result.ok() ? pouch.health : "degraded";
    out.event.latency_ns = starryos.result.latency_ns;
    out.trace_complete = !out.event.trace_id.empty() &&
                         out.event.record_ref.record_id != 0 &&
                         out.event.kernel_request_ref.record_id != 0 &&
                         out.event.kernel_result_ref.record_id != 0;
    out.board_real_claim = false;
    return out;
  }
};

}  // namespace asking_star::v55
