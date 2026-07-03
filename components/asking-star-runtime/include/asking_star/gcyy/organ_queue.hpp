#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/gcyy/digital_cell.hpp"

#include <deque>
#include <optional>
#include <string>

namespace asking_star::gcyy {

// FIFO queue for mock OrganRuntime execution.
class OrganQueue {
 public:
  explicit OrganQueue(std::string organ_id);

  void push(DigitalCell cell);
  void push_ref(asking_star::v5::DigitalSetRefRecord cell_ref);
  [[nodiscard]] std::optional<DigitalCell> pop();
  [[nodiscard]] std::optional<asking_star::v5::DigitalSetRefRecord> pop_ref();
  [[nodiscard]] bool empty() const;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] const std::string& organ_id() const;

 private:
  std::string organ_id_;
  std::deque<DigitalCell> cells_;
  std::deque<asking_star::v5::DigitalSetRefRecord> cell_refs_;
};

}  // namespace asking_star::gcyy
