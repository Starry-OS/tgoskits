#pragma once

#include "asking_star/v55/chamber_pouch.hpp"
#include "asking_star/v55/pouch_trace_bridge.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

struct ReplayAiResultRecord {
  std::uint64_t result_id{0};
  std::string trace_id;
  std::string source_name{"fixture"};
  std::string tensor_hash;
  std::string payload_json;
  bool real_sensor_claim{false};
};

struct ReplayAiChamberRecord {
  ChamberExecutionRecord execution;
  ChamberPouchRecord pouch;
  asking_star::v5::TraceEventRecord trace;
  bool replay_claim{true};
  bool real_sensor_claim{false};
};

class ReplayAiChamber {
 public:
  [[nodiscard]] ReplayAiChamberRecord replay(
      const ReplayAiResultRecord& ai_result,
      const ChamberPlacementRecord& placement,
      std::uint64_t logical_order) const {
    ReplayAiChamberRecord record;
    record.execution.execution_id = ai_result.result_id + 7000;
    record.execution.placement_id = placement.placement_id;
    record.execution.adapter_mode = AdapterMode::Replay;
    record.execution.request_payload =
        "source=" + ai_result.source_name + ";tensor_hash=" +
        ai_result.tensor_hash + ";payload=" + ai_result.payload_json;

    ChamberPouchView pouch_view;
    record.pouch = pouch_view.observe(record.execution,
                                      record.execution.request_payload,
                                      !ai_result.tensor_hash.empty());
    record.pouch.fallback =
        ai_result.tensor_hash.empty() ? "missing-tensor-hash" : "";

    StarryOSDryRunBridgeRecord dryrun_shadow;
    dryrun_shadow.request.trace_id = ai_result.trace_id;
    dryrun_shadow.result.status = asking_star::soil::SoilExecutionStatus::Ok;
    dryrun_shadow.result.trace_id = ai_result.trace_id;
    PouchTraceBridge trace_bridge;
    record.trace =
        trace_bridge.record(record.execution, record.pouch, dryrun_shadow,
                            logical_order)
            .event;
    record.trace.adapter_mode = "Replay";
    record.replay_claim = true;
    record.real_sensor_claim = false;
    return record;
  }
};

}  // namespace asking_star::v55
