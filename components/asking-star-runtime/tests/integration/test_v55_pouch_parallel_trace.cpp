#include "asking_star/v55/chamber_starryos_dryrun_bridge.hpp"
#include "asking_star/v55/pouch_trace_bridge.hpp"

#include <cassert>

int main() {
  using asking_star::v5::RecordTypeTag;
  using asking_star::v55::AdapterMode;
  using asking_star::v55::ChamberExecutionRecord;
  using asking_star::v55::ChamberPouchView;
  using asking_star::v55::ChamberStarryOSDryRunBridge;
  using asking_star::v55::PouchTraceBridge;

  const ChamberExecutionRecord execution{88, 55, AdapterMode::DryRun,
                                         "log-write trace path"};
  const ChamberStarryOSDryRunBridge starryos_bridge;
  const auto starryos = starryos_bridge.execute(execution);
  assert(starryos.result.ok());

  const ChamberPouchView pouch_view;
  const auto pouch = pouch_view.observe(execution, starryos.result.payload, true);

  const PouchTraceBridge trace_bridge;
  const auto trace = trace_bridge.record(execution, pouch, starryos, 7);
  assert(trace.trace_complete);
  assert(!trace.board_real_claim);
  assert(trace.event.trace_id == starryos.request.trace_id);
  assert(trace.event.record_ref.expected_type_tag == RecordTypeTag::TraceEvent);
  assert(trace.event.kernel_request_ref.expected_type_tag ==
         RecordTypeTag::KernelRequest);
  assert(trace.event.kernel_result_ref.expected_type_tag ==
         RecordTypeTag::KernelResult);
  assert(trace.event.organ_result_ref.record_id == pouch.pouch_id);
  assert(trace.event.adapter_mode == "DryRun");
  assert(trace.event.logical_order == 7);
  assert(trace.event.status == "healthy");

  const ChamberExecutionRecord board_execution{89, 55, AdapterMode::BoardReal,
                                               "log-write board guard"};
  const auto board_starryos = starryos_bridge.execute(board_execution);
  const auto board_pouch =
      pouch_view.observe(board_execution, board_starryos.result.payload, false);
  const auto board_trace =
      trace_bridge.record(board_execution, board_pouch, board_starryos, 8);
  assert(board_trace.trace_complete);
  assert(!board_trace.board_real_claim);
  assert(board_trace.event.adapter_mode == "BoardReal");
  assert(board_trace.event.status == "degraded");

  return 0;
}
