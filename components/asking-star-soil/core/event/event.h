#pragma once

#include "common_types.h"

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace asking_star::core::event {

using EventHandler = std::function<void(const asking_star::Event&)>;

class EventStore {
 public:
  asking_star::Event append(asking_star::EventType type, std::string id,
                            std::string payload);

  [[nodiscard]] const std::vector<asking_star::Event>& list() const noexcept;
  [[nodiscard]] std::vector<asking_star::Event> replay() const;

 private:
  std::uint64_t next_sequence_{1};
  std::vector<asking_star::Event> events_;
};

class EventBus {
 public:
  void subscribe(EventHandler handler);
  void publish(const asking_star::Event& event) const;
  [[nodiscard]] std::size_t subscriber_count() const noexcept;

 private:
  std::vector<EventHandler> handlers_;
};

}  // namespace asking_star::core::event
