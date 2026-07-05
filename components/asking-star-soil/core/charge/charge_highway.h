#pragma once

#include "core/charge/charge_frame.h"

#include <deque>
#include <optional>

namespace asking_star::core::charge {

class ChargeHighway {
 public:
  void push(ChargeFrame frame) {
    frame.add_trace("highway:push");
    frames_.push_back(std::move(frame));
  }

  [[nodiscard]] std::optional<ChargeFrame> pop_next() {
    if (frames_.empty()) {
      return std::nullopt;
    }
    auto frame = std::move(frames_.front());
    frames_.pop_front();
    frame.add_trace("highway:pop");
    return frame;
  }

  [[nodiscard]] std::size_t backlog() const { return frames_.size(); }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }

 private:
  std::deque<ChargeFrame> frames_;
};

}  // namespace asking_star::core::charge
