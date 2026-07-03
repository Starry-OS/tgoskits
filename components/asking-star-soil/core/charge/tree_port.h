#pragma once

#include "core/charge/charge_protocol.h"
#include "core/charge/tree_stack.h"

#include <string>
#include <vector>

namespace asking_star::core::charge {

struct TreePortDescriptor {
  std::string tree_id;
  std::vector<ChargeProtocol> accepted_protocols;
  std::vector<std::string> accepted_capabilities;
  std::vector<Layer> accepted_layers;
  std::size_t max_backlog{16};
  bool shadow_guard{false};

  [[nodiscard]] bool is_valid() const {
    return !tree_id.empty() && !accepted_protocols.empty() &&
           !accepted_capabilities.empty() && !accepted_layers.empty() &&
           max_backlog > 0;
  }
};

class TreePort {
 public:
  explicit TreePort(TreePortDescriptor descriptor)
      : descriptor_(std::move(descriptor)) {}

  [[nodiscard]] const TreePortDescriptor& descriptor() const {
    return descriptor_;
  }

  [[nodiscard]] bool can_accept_more() const {
    return ingress_.backlog() < descriptor_.max_backlog;
  }

  void push_ingress(ChargeFrame frame) {
    frame.current_tree = descriptor_.tree_id;
    frame.add_trace("tree:" + descriptor_.tree_id + ":ingress");
    ingress_.push_back(std::move(frame));
  }

  [[nodiscard]] std::optional<ChargeFrame> pop_ingress() {
    return ingress_.pop_front();
  }

  void push_egress(ChargeFrame frame) {
    frame.current_tree = descriptor_.tree_id;
    frame.add_trace("tree:" + descriptor_.tree_id + ":egress");
    egress_.push_back(std::move(frame));
  }

  [[nodiscard]] std::optional<ChargeFrame> pop_egress() {
    return egress_.pop_front();
  }

  [[nodiscard]] std::size_t ingress_backlog() const {
    return ingress_.backlog();
  }

  [[nodiscard]] std::size_t egress_backlog() const {
    return egress_.backlog();
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }

 private:
  TreePortDescriptor descriptor_;
  TreeIngressStack ingress_;
  TreeEgressStack egress_;
};

}  // namespace asking_star::core::charge
