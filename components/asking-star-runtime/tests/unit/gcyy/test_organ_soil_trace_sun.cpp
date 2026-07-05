#include "asking_star/gcyy/log_organ.hpp"
#include "asking_star/gcyy/mock_kernel_adapter.hpp"
#include "asking_star/gcyy/return_rebuilder.hpp"
#include "asking_star/gcyy/shadowguard_trace_adapter.hpp"
#include "asking_star/gcyy/soil_runtime.hpp"
#include "asking_star/gcyy/sun_orchestrator.hpp"

#include <cassert>

namespace {

asking_star::gcyy::DigitalCell make_cell() {
  asking_star::gcyy::GeneView gene;
  gene.gene_id = "gene-1";
  gene.trace_id = "trace-1";
  gene.state_hash = "state";
  gene.semantic_hash = "semantic";
  asking_star::gcyy::ChargeView charge;
  charge.charge_id = "charge-1";
  charge.origin_gene_id = "gene-1";
  charge.trace_id = "trace-1";
  charge.capability_kind = "mock.execute";
  asking_star::gcyy::DigitalCell cell;
  cell.cell_id = "cell-1";
  cell.trace_id = "trace-1";
  cell.gene = gene;
  cell.charge = charge;
  cell.state = asking_star::gcyy::DigitalCellState::ChargeReady;
  return cell;
}

}  // namespace

int main() {
  auto cell = make_cell();
  asking_star::gcyy::SunOrchestrator sun;
  auto tick = sun.next_tick(cell.trace_id);
  assert(tick.tick_id == 1);
  asking_star::gcyy::RuntimeBudget budget{"budget-1", cell.trace_id, 1, 1};
  assert(sun.admit(cell, budget).ok());
  assert(budget.consume(1).ok());
  assert(!budget.consume(1).ok());

  asking_star::gcyy::LogOrgan organ("log-organ");
  auto organ_result = organ.execute(cell);
  assert(organ_result.ok());
  assert(organ_result.trace_id == cell.trace_id);

  asking_star::gcyy::SoilRuntime soil;
  asking_star::gcyy::KernelRequest request;
  assert(soil.make_request(cell, request).ok());
  assert(request.dry_run);
  asking_star::gcyy::MockKernelAdapter adapter;
  auto result = adapter.submit(request);
  assert(result.ok());

  asking_star::gcyy::ReturnRebuilder rebuilder;
  asking_star::gcyy::DigitalSetFragment fragment;
  assert(rebuilder.rebuild(result, fragment).ok());
  assert(fragment.trace_id == cell.trace_id);

  asking_star::gcyy::TraceSink sink;
  asking_star::gcyy::ShadowGuardTraceAdapter trace(sink);
  trace.record(cell.trace_id, "organ_executed", "ok");
  assert(sink.size() == 1);
  assert(sink.events()[0].trace_id == cell.trace_id);
  return 0;
}

