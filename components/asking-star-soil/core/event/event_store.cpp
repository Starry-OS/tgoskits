#include "core/event/event.h"

#include <stdexcept>
#include <utility>

namespace asking_star::core::event {

asking_star::Event EventStore::append(asking_star::EventType type,
                                      std::string id, std::string payload) {
  asking_star::Event event{
      next_sequence_++,
      type,
      std::move(id),
      std::move(payload),
      asking_star::now(),
  };
  if (!event.is_valid()) {
    throw std::invalid_argument("event id must not be empty");
  }
  events_.push_back(event);
  return event;
}

const std::vector<asking_star::Event>& EventStore::list() const noexcept {
  return events_;
}

std::vector<asking_star::Event> EventStore::replay() const {
  return events_;
}

}  // namespace asking_star::core::event
