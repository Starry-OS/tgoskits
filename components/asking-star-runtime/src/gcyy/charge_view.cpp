#include "asking_star/gcyy/charge_view.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool ChargeView::has_trace() const { return !trace_id.empty(); }

bool ChargeView::is_expired_at(std::uint64_t tick) const {
  return lifetime_tick != 0 && tick >= lifetime_tick;
}

GcyyResult ChargeView::validate() const {
  if (charge_id.empty() || origin_gene_id.empty() || capability_kind.empty()) {
    return GcyyResult::failure(GcyyStatus::InvalidArgument,
                               "charge identity fields are required");
  }
  if (!has_trace()) {
    return GcyyResult::failure(GcyyStatus::MissingTraceId,
                               "charge trace_id is required");
  }
  return GcyyResult::success();
}

std::string ChargeView::debug_dump() const {
  std::ostringstream out;
  out << "ChargeView{id=" << charge_id << ", origin_gene=" << origin_gene_id
      << ", trace=" << trace_id << ", capability=" << capability_kind
      << ", priority=" << priority << ", lifetime_tick=" << lifetime_tick
      << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

