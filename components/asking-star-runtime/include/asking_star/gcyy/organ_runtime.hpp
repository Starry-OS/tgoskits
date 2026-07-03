#pragma once

#include "asking_star/gcyy/digital_cell.hpp"

#include <string>

namespace asking_star::gcyy {

struct OrganResult {
  std::string organ_id;
  std::string cell_id;
  std::string trace_id;
  GcyyStatus status{GcyyStatus::Ok};
  std::string message;

  [[nodiscard]] bool ok() const;
  [[nodiscard]] std::string debug_dump() const;
};

// OrganRuntime consumes DigitalCell without reinterpreting DigitalSet.
class OrganRuntime {
 public:
  virtual ~OrganRuntime() = default;
  [[nodiscard]] virtual OrganResult execute(const DigitalCell& cell) const = 0;
};

}  // namespace asking_star::gcyy

