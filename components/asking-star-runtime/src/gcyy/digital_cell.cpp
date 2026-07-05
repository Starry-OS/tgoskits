#include "asking_star/gcyy/digital_cell.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool DigitalCell::has_trace() const { return !trace_id.empty(); }

bool DigitalCell::has_charge() const { return charge.has_value(); }

GcyyResult DigitalCell::validate() const {
  if (cell_id.empty()) {
    return GcyyResult::failure(GcyyStatus::InvalidArgument,
                               "cell_id is required");
  }
  if (!has_trace()) {
    return GcyyResult::failure(GcyyStatus::MissingTraceId,
                               "cell trace_id is required");
  }
  auto gene_result = gene.validate();
  if (!gene_result.ok()) {
    return GcyyResult::failure(GcyyStatus::MissingGene,
                               "valid GeneView is required");
  }
  if (charge.has_value()) {
    auto charge_result = charge->validate();
    if (!charge_result.ok()) {
      return charge_result;
    }
    if (charge->origin_gene_id != gene.gene_id) {
      return GcyyResult::failure(GcyyStatus::InvalidState,
                                 "charge origin_gene_id must match gene_id");
    }
  }
  return GcyyResult::success();
}

std::string DigitalCell::debug_dump() const {
  std::ostringstream out;
  out << "DigitalCell{id=" << cell_id << ", trace=" << trace_id
      << ", gene=" << gene.gene_id << ", has_charge="
      << (has_charge() ? "true" : "false") << ", state=" << to_string(state)
      << "}";
  return out.str();
}

const char* to_string(DigitalCellState state) {
  switch (state) {
    case DigitalCellState::Created:
      return "created";
    case DigitalCellState::GeneReady:
      return "gene_ready";
    case DigitalCellState::ChargeReady:
      return "charge_ready";
    case DigitalCellState::Scheduled:
      return "scheduled";
    case DigitalCellState::Running:
      return "running";
    case DigitalCellState::Returned:
      return "returned";
    case DigitalCellState::Compressed:
      return "compressed";
    case DigitalCellState::Archived:
      return "archived";
    case DigitalCellState::Rejected:
      return "rejected";
    case DigitalCellState::Expired:
      return "expired";
  }
  return "created";
}

}  // namespace asking_star::gcyy

