#pragma once

#include "common_types.h"
#include "core/statechain/state_gene_id.h"

#include <optional>
#include <string>

namespace asking_star::core::statechain {

enum class GenerationStatus {
  Pending,
  Generated,
  Rejected,
  Sealed,
};

struct StateGeneFragment {
  StateGeneId id;
  std::optional<StateGeneId> parent;
  std::string owner_object;
  std::string object_kind;
  std::string xing_snapshot;
  std::string ming_snapshot;
  std::string sheng_rule;
  std::string inertia_profile;
  std::string influence_digest;
  asking_star::StateDiff diff;
  asking_star::RuntimeMode mode{asking_star::RuntimeMode::AskingStar};
  std::string salt;
  asking_star::Timestamp created_at{asking_star::now()};
  GenerationStatus status{GenerationStatus::Pending};
  std::string reason;

  [[nodiscard]] bool is_valid() const {
    return id.is_valid() && !owner_object.empty() && !object_kind.empty() &&
           diff.is_valid() && !reason.empty();
  }
};

inline const char* to_string(GenerationStatus status) {
  switch (status) {
    case GenerationStatus::Pending:
      return "pending";
    case GenerationStatus::Generated:
      return "generated";
    case GenerationStatus::Rejected:
      return "rejected";
    case GenerationStatus::Sealed:
      return "sealed";
  }
  return "pending";
}

}  // namespace asking_star::core::statechain
