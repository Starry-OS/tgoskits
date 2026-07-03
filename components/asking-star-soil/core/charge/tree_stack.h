#pragma once

#include "core/charge/charge_frame.h"

#include <deque>
#include <optional>

namespace asking_star::core::charge {

class TreeStack {
 public:
  void push_back(ChargeFrame frame) { frames_.push_back(std::move(frame)); }

  [[nodiscard]] std::optional<ChargeFrame> pop_front() {
    if (frames_.empty()) {
      return std::nullopt;
    }
    auto frame = std::move(frames_.front());
    frames_.pop_front();
    return frame;
  }

  [[nodiscard]] std::optional<ChargeFrame> peek_front() const {
    if (frames_.empty()) {
      return std::nullopt;
    }
    return frames_.front();
  }

  [[nodiscard]] std::size_t backlog() const { return frames_.size(); }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }

 private:
  std::deque<ChargeFrame> frames_;
};

using TreeIngressStack = TreeStack;
using TreeEgressStack = TreeStack;

}  // namespace asking_star::core::charge
