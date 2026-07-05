#pragma once

#include "core/charge/charge_frame.h"
#include "core/gene/gene_code.h"

#include <optional>
#include <string>

namespace asking_star::core::charge {

struct TreeOutput {
  std::string tree_id;
  std::optional<ChargeFrame> return_frame;
  std::optional<asking_star::core::gene::GeneCode> gene_candidate;
  std::string reason;

  [[nodiscard]] bool is_valid() const {
    return !tree_id.empty() && (!reason.empty()) &&
           (return_frame.has_value() || gene_candidate.has_value());
  }

  [[nodiscard]] bool writes_genebank() const { return false; }

  [[nodiscard]] bool executes_kernel_soil() const { return false; }
};

}  // namespace asking_star::core::charge
