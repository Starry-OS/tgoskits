#pragma once

#include "core/dualchain/dual_gene_anchor.h"
#include "core/responsibility/responsibility_trace.h"
#include "core/statechain/state_gene_fragment.h"

#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace asking_star::core::genebank {

class StateChainStore {
 public:
  void append(asking_star::core::statechain::StateGeneFragment fragment) {
    const auto id = fragment.id.value;
    fragments_by_id_[id] = std::move(fragment);
    order_.push_back(id);
  }

  [[nodiscard]] std::optional<asking_star::core::statechain::StateGeneFragment>
  get(const asking_star::core::statechain::StateGeneId& id) const {
    auto it = fragments_by_id_.find(id.value);
    if (it == fragments_by_id_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] std::vector<asking_star::core::statechain::StateGeneFragment>
  all() const {
    std::vector<asking_star::core::statechain::StateGeneFragment> result;
    for (const auto& id : order_) {
      result.push_back(fragments_by_id_.at(id));
    }
    return result;
  }

 private:
  std::unordered_map<std::string,
                     asking_star::core::statechain::StateGeneFragment>
      fragments_by_id_;
  std::vector<std::string> order_;
};

class ResponsibilityChainStore {
 public:
  void append(asking_star::core::responsibility::ResponsibilityTrace trace) {
    const auto id = trace.id.value;
    traces_by_id_[id] = std::move(trace);
    order_.push_back(id);
  }

  [[nodiscard]] std::optional<
      asking_star::core::responsibility::ResponsibilityTrace>
  get(const asking_star::core::responsibility::ResponsibilityTraceId& id) const {
    auto it = traces_by_id_.find(id.value);
    if (it == traces_by_id_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] std::vector<
      asking_star::core::responsibility::ResponsibilityTrace>
  all() const {
    std::vector<asking_star::core::responsibility::ResponsibilityTrace> result;
    for (const auto& id : order_) {
      result.push_back(traces_by_id_.at(id));
    }
    return result;
  }

 private:
  std::unordered_map<std::string,
                     asking_star::core::responsibility::ResponsibilityTrace>
      traces_by_id_;
  std::vector<std::string> order_;
};

class DualLinkIndex {
 public:
  void index(const asking_star::core::dualchain::DualGeneAnchor& anchor) {
    state_to_trace_[anchor.state_gene_id.value] = anchor.trace_id.value;
    trace_to_state_[anchor.trace_id.value] = anchor.state_gene_id.value;
    anchors_by_hash_[anchor.link_hash.digest.value] = anchor;
  }

  [[nodiscard]] std::optional<
      asking_star::core::responsibility::ResponsibilityTraceId>
  trace_for_state(
      const asking_star::core::statechain::StateGeneId& id) const {
    auto it = state_to_trace_.find(id.value);
    if (it == state_to_trace_.end()) {
      return std::nullopt;
    }
    return asking_star::core::responsibility::ResponsibilityTraceId{it->second};
  }

  [[nodiscard]] std::optional<asking_star::core::statechain::StateGeneId>
  state_for_trace(
      const asking_star::core::responsibility::ResponsibilityTraceId& id) const {
    auto it = trace_to_state_.find(id.value);
    if (it == trace_to_state_.end()) {
      return std::nullopt;
    }
    return asking_star::core::statechain::StateGeneId{it->second};
  }

  [[nodiscard]] std::optional<asking_star::core::dualchain::DualGeneAnchor>
  anchor_for_hash(
      const asking_star::core::dualchain::DualLinkHash& hash) const {
    auto it = anchors_by_hash_.find(hash.digest.value);
    if (it == anchors_by_hash_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

 private:
  std::unordered_map<std::string, std::string> state_to_trace_;
  std::unordered_map<std::string, std::string> trace_to_state_;
  std::unordered_map<std::string, asking_star::core::dualchain::DualGeneAnchor>
      anchors_by_hash_;
};

struct DualReplayRecord {
  asking_star::core::statechain::StateGeneFragment state;
  asking_star::core::responsibility::ResponsibilityTrace trace;
  asking_star::core::dualchain::DualGeneAnchor anchor;
};

class GeneBank {
 public:
  void append_state(
      asking_star::core::statechain::StateGeneFragment fragment) {
    if (!fragment.is_valid()) {
      throw std::invalid_argument("invalid state gene fragment");
    }
    state_store_.append(std::move(fragment));
  }

  void append_trace(
      asking_star::core::responsibility::ResponsibilityTrace trace) {
    if (!trace.is_valid()) {
      throw std::invalid_argument("invalid responsibility trace");
    }
    responsibility_store_.append(std::move(trace));
  }

  void anchor_dual_link(
      const asking_star::core::dualchain::DualGeneAnchor& anchor) {
    if (!anchor.is_valid()) {
      throw std::invalid_argument("invalid dual gene anchor");
    }
    if (!state_store_.get(anchor.state_gene_id).has_value()) {
      throw std::invalid_argument("missing state fragment for anchor");
    }
    if (!responsibility_store_.get(anchor.trace_id).has_value()) {
      throw std::invalid_argument("missing responsibility trace for anchor");
    }
    dual_index_.index(anchor);
  }

  [[nodiscard]] std::optional<asking_star::core::statechain::StateGeneFragment>
  get_state(const asking_star::core::statechain::StateGeneId& id) const {
    return state_store_.get(id);
  }

  [[nodiscard]] std::optional<
      asking_star::core::responsibility::ResponsibilityTrace>
  get_trace(
      const asking_star::core::responsibility::ResponsibilityTraceId& id) const {
    return responsibility_store_.get(id);
  }

  [[nodiscard]] std::optional<
      asking_star::core::responsibility::ResponsibilityTraceId>
  trace_for_state(
      const asking_star::core::statechain::StateGeneId& id) const {
    return dual_index_.trace_for_state(id);
  }

  [[nodiscard]] std::optional<asking_star::core::statechain::StateGeneId>
  state_for_trace(
      const asking_star::core::responsibility::ResponsibilityTraceId& id) const {
    return dual_index_.state_for_trace(id);
  }

  [[nodiscard]] std::optional<DualReplayRecord> replay_dual_link(
      const asking_star::core::dualchain::DualLinkHash& hash) const {
    auto anchor = dual_index_.anchor_for_hash(hash);
    if (!anchor.has_value()) {
      return std::nullopt;
    }
    auto state = state_store_.get(anchor->state_gene_id);
    auto trace = responsibility_store_.get(anchor->trace_id);
    if (!state.has_value() || !trace.has_value()) {
      return std::nullopt;
    }
    return DualReplayRecord{*state, *trace, *anchor};
  }

 private:
  StateChainStore state_store_;
  ResponsibilityChainStore responsibility_store_;
  DualLinkIndex dual_index_;
};

}  // namespace asking_star::core::genebank
