#include "core/event/event.h"

#include <stdexcept>

namespace asking_star::core::event {

void EventBus::subscribe(EventHandler handler) {
  if (!handler) {
    throw std::invalid_argument("event handler must be callable");
  }
  handlers_.push_back(std::move(handler));
}

void EventBus::publish(const asking_star::Event& event) const {
  if (!event.is_valid()) {
    throw std::invalid_argument("event must be valid before publishing");
  }
  for (const auto& handler : handlers_) {
    handler(event);
  }
}

std::size_t EventBus::subscriber_count() const noexcept {
  return handlers_.size();
}

}  // namespace asking_star::core::event
