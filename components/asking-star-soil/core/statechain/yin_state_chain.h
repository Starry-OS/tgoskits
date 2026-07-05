#pragma once

#include "core/statechain/state_gene_fragment.h"

#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace asking_star::core::statechain {

struct StateChainHead {
  StateGeneId id;
  std::string branch{"main"};
  bool sealed{false};

  [[nodiscard]] bool is_valid() const {
    return id.is_valid() && !branch.empty();
  }
};

enum class YinStateEventType {
  Appended,
  Branched,
  Sealed,
  Promoted,
  ShadowObserved,
};

struct YinStateEvent {
  YinStateEventType type{YinStateEventType::Appended};
  StateGeneId fragment_id;
  std::string branch;
  std::string reason;
  asking_star::Timestamp occurred_at{asking_star::now()};

  [[nodiscard]] bool is_valid() const {
    return fragment_id.is_valid() && !branch.empty() && !reason.empty();
  }
};

class YinStateChain {
 public:
  void append(StateGeneFragment fragment, std::string branch = "main") {
    append_internal(std::move(fragment), std::move(branch), true, "append");
  }

  void observe_shadow(StateGeneFragment fragment, std::string branch = "shadow") {
    fragment.mode = asking_star::RuntimeMode::ShadowGuard;
    append_internal(std::move(fragment), std::move(branch), false,
                    "shadow observation");
  }

  StateGeneFragment branch(const StateGeneId& parent, StateGeneFragment fragment,
                           std::string branch_name) {
    if (!get(parent).has_value()) {
      throw std::invalid_argument("branch parent is missing");
    }
    fragment.parent = parent;
    append_internal(fragment, branch_name, true, "branch from parent");
    return fragment;
  }

  void seal(const std::string& branch, const std::string& reason) {
    auto it = heads_by_branch_.find(branch);
    if (it == heads_by_branch_.end() || reason.empty()) {
      throw std::invalid_argument("cannot seal missing branch");
    }
    it->second.sealed = true;
    events_.push_back(
        {YinStateEventType::Sealed, it->second.id, branch, reason});
  }

  void promote_head(const StateGeneId& id, std::string branch,
                    std::string reason) {
    if (!get(id).has_value() || branch.empty() || reason.empty()) {
      throw std::invalid_argument("cannot promote missing fragment");
    }
    heads_by_branch_[branch] = StateChainHead{id, branch, false};
    events_.push_back({YinStateEventType::Promoted, id, branch, reason});
  }

  [[nodiscard]] std::optional<StateGeneFragment> get(
      const StateGeneId& id) const {
    auto it = fragments_by_id_.find(id.value);
    if (it == fragments_by_id_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] std::optional<StateChainHead> head(
      const std::string& branch = "main") const {
    auto it = heads_by_branch_.find(branch);
    if (it == heads_by_branch_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] const std::vector<YinStateEvent>& events() const {
    return events_;
  }

 private:
  void append_internal(StateGeneFragment fragment, std::string branch,
                       bool promote, std::string reason) {
    if (!fragment.is_valid() || branch.empty()) {
      throw std::invalid_argument("invalid state fragment append");
    }
    const auto id = fragment.id;
    fragments_by_id_[id.value] = std::move(fragment);
    order_.push_back(id.value);
    events_.push_back({promote ? YinStateEventType::Appended
                               : YinStateEventType::ShadowObserved,
                       id, branch, reason});
    if (promote) {
      promote_head(id, std::move(branch), "append promoted head");
    }
  }

  std::unordered_map<std::string, StateGeneFragment> fragments_by_id_;
  std::vector<std::string> order_;
  std::unordered_map<std::string, StateChainHead> heads_by_branch_;
  std::vector<YinStateEvent> events_;
};

}  // namespace asking_star::core::statechain
