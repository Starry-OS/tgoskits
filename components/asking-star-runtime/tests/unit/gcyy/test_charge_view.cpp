#include "asking_star/gcyy/charge_view.hpp"

#include <cassert>
#include <string>

int main() {
  asking_star::gcyy::ChargeView charge;
  charge.charge_id = "charge-1";
  charge.origin_gene_id = "gene-1";
  charge.trace_id = "trace-1";
  charge.projection_id = "projection-1";
  charge.capability_kind = "mock.execute";
  charge.execution_intent = "echo";
  charge.runtime_budget = "budget-1";
  charge.priority = 7;
  charge.payload_ref = "payload://charge/1";
  charge.lifetime_tick = 10;

  assert(charge.has_trace());
  assert(charge.validate().ok());
  assert(!charge.is_expired_at(9));
  assert(charge.is_expired_at(10));
  assert(charge.debug_dump().find("mock.execute") != std::string::npos);

  charge.trace_id.clear();
  auto missing_trace = charge.validate();
  assert(!missing_trace.ok());
  assert(missing_trace.status == asking_star::gcyy::GcyyStatus::MissingTraceId);

  return 0;
}

