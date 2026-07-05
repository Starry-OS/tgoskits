#pragma once

#include "asking_star/gcyy/charge_view.hpp"
#include "asking_star/gcyy/gene_view.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"

#include <optional>
#include <string>

namespace asking_star::gcyy {

enum class DigitalCellState {
  Created,
  GeneReady,
  ChargeReady,
  Scheduled,
  Running,
  Returned,
  Compressed,
  Archived,
  Rejected,
  Expired,
};

// DigitalCell is the minimum semantic runtime unit: Gene plus optional Charge.
struct DigitalCell {
  std::string cell_id;
  std::string trace_id;
  GeneView gene;
  std::optional<ChargeView> charge;
  std::string star_tag;
  std::string pointer_anchor;
  DigitalCellState state{DigitalCellState::Created};

  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] bool has_charge() const;
  [[nodiscard]] GcyyResult validate() const;
  [[nodiscard]] std::string debug_dump() const;
};

[[nodiscard]] const char* to_string(DigitalCellState state);

}  // namespace asking_star::gcyy

