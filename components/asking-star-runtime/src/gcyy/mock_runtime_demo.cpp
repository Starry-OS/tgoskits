#include "asking_star/gcyy/mock_runtime_demo.hpp"

#include "asking_star/gcyy/log_organ.hpp"
#include "asking_star/gcyy/mock_kernel_adapter.hpp"
#include "asking_star/gcyy/mock_yang_operator.hpp"
#include "asking_star/gcyy/mock_yin_operator.hpp"
#include "asking_star/gcyy/return_rebuilder.hpp"
#include "asking_star/gcyy/shadowguard_trace_adapter.hpp"
#include "asking_star/gcyy/soil_runtime.hpp"
#include "asking_star/gcyy/star_projection.hpp"
#include "asking_star/gcyy/sun_orchestrator.hpp"

#include <cstddef>

namespace asking_star::gcyy {

std::vector<std::string> run_mock_runtime_demo() {
  std::vector<std::string> log;
  TraceSink sink;
  ShadowGuardTraceAdapter trace(sink);

  DigitalSetFragment fragment{"fragment-demo",
                              "mock-input",
                              "trace-demo",
                              "demo.input",
                              "star://demo/input",
                              {std::byte{'d'}, std::byte{'o'}},
                              "hash-demo",
                              "gcyy.fragment.v1"};
  trace.record(fragment.trace_id, "fragment_created", "fragment created");
  log.push_back("[Walker] fragment created");

  ProjectionContext context{"projection-demo", fragment.trace_id,
                            ProjectionMode::AskingStar, "budget-demo",
                            "mock-rule-v1", true};
  MockYinOperator yin;
  MockYangOperator yang;
  StarProjection projection(yin, yang);
  GeneView gene;
  auto gene_result = projection.project_to_gene(fragment, context, gene);
  if (!gene_result.ok()) {
    return {"[Error] gene projection failed"};
  }
  trace.record(gene.trace_id, "gene_generated", "gene generated");
  log.push_back("[Yin] gene generated");

  ChargeView charge;
  auto charge_result = projection.project_to_charge(gene, context, charge);
  if (!charge_result.ok()) {
    return {"[Error] charge projection failed"};
  }
  trace.record(charge.trace_id, "charge_generated", "charge generated");
  log.push_back("[Yang] charge generated");

  DigitalCell cell;
  auto cell_result = projection.make_cell(gene, charge, context, cell);
  if (!cell_result.ok()) {
    return {"[Error] digital cell failed"};
  }
  trace.record(cell.trace_id, "cell_ready", "digital cell ready");
  log.push_back("[Cell] digital cell ready");

  SunOrchestrator sun;
  RuntimeBudget budget{"budget-demo", cell.trace_id, 2, 1};
  auto tick = sun.next_tick(cell.trace_id);
  auto admit_result = sun.admit(cell, budget);
  if (tick.tick_id == 0 || !admit_result.ok()) {
    return {"[Error] sun admission failed"};
  }
  log.push_back("[Sun] admitted");

  LogOrgan organ("log-organ");
  auto organ_result = organ.execute(cell);
  if (!organ_result.ok()) {
    return {"[Error] organ failed"};
  }
  log.push_back("[Organ] executed");

  SoilRuntime soil;
  KernelRequest request;
  auto request_result = soil.make_request(cell, request);
  if (!request_result.ok()) {
    return {"[Error] soil request failed"};
  }
  MockKernelAdapter adapter;
  auto result = adapter.submit(request);
  log.push_back("[Soil] kernel request mocked");

  ReturnRebuilder rebuilder;
  DigitalSetFragment rebuilt;
  auto rebuild_result = rebuilder.rebuild(result, rebuilt);
  if (!rebuild_result.ok()) {
    return {"[Error] return rebuild failed"};
  }
  log.push_back("[ReturnRebuilder] digitalset rebuilt");

  trace.record(cell.trace_id, "complete", "complete");
  log.push_back("[Trace] complete");
  return log;
}

}  // namespace asking_star::gcyy
