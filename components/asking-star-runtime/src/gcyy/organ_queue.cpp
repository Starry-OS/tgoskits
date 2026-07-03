#include "asking_star/gcyy/organ_queue.hpp"

#include <functional>
#include <utility>

namespace asking_star::gcyy {

OrganQueue::OrganQueue(std::string organ_id) : organ_id_(std::move(organ_id)) {}

void OrganQueue::push(DigitalCell cell) {
  asking_star::v5::DigitalSetRefRecord ref;
  ref.record_id = std::hash<std::string>{}(cell.cell_id);
  ref.expected_type_tag = asking_star::v5::RecordTypeTag::DigitalCell;
  ref.trace_id = cell.trace_id;
  cell_refs_.push_back(ref);
  cells_.push_back(std::move(cell));
}

void OrganQueue::push_ref(asking_star::v5::DigitalSetRefRecord cell_ref) {
  cell_refs_.push_back(std::move(cell_ref));
}

std::optional<DigitalCell> OrganQueue::pop() {
  if (cells_.empty()) {
    return std::nullopt;
  }
  auto cell = std::move(cells_.front());
  cells_.pop_front();
  if (!cell_refs_.empty()) {
    cell_refs_.pop_front();
  }
  return cell;
}

std::optional<asking_star::v5::DigitalSetRefRecord> OrganQueue::pop_ref() {
  if (cell_refs_.empty()) {
    return std::nullopt;
  }
  auto ref = std::move(cell_refs_.front());
  cell_refs_.pop_front();
  return ref;
}

bool OrganQueue::empty() const { return cell_refs_.empty() && cells_.empty(); }

std::size_t OrganQueue::size() const { return cell_refs_.size(); }

const std::string& OrganQueue::organ_id() const { return organ_id_; }

}  // namespace asking_star::gcyy
