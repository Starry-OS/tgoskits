#include "asking_star/gcyy/log_organ.hpp"

#include <utility>

namespace asking_star::gcyy {

LogOrgan::LogOrgan(std::string organ_id) : organ_id_(std::move(organ_id)) {}

OrganResult LogOrgan::execute(const DigitalCell& cell) const {
  auto result = cell.validate();
  if (!result.ok()) {
    return OrganResult{organ_id_, cell.cell_id, cell.trace_id, result.status,
                       result.message};
  }
  return OrganResult{organ_id_, cell.cell_id, cell.trace_id, GcyyStatus::Ok,
                     "mock organ executed"};
}

}  // namespace asking_star::gcyy

