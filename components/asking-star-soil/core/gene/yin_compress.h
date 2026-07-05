#pragma once

#include "core/charge/charge_flow.h"
#include "core/gene/gene_code.h"
#include "core/responsibility/responsibility_trace.h"
#include "core/responsibility/responsibility_trace_id.h"
#include "core/statechain/state_gene_fragment.h"
#include "core/statechain/state_gene_id.h"

namespace asking_star::core::gene {

struct YinCompressResult {
  GeneCode gene_code;
  asking_star::core::statechain::StateGeneFragment state_candidate;
  asking_star::core::responsibility::ResponsibilityTrace trace_candidate;

  [[nodiscard]] bool is_valid() const {
    return gene_code.is_valid() && state_candidate.is_valid() &&
           trace_candidate.is_valid();
  }

  [[nodiscard]] bool bypasses_gene_protocol() const { return false; }
};

class YinCompress {
 public:
  [[nodiscard]] YinCompressResult compress(
      const asking_star::core::charge::ChargeFlow& flow) const {
    const auto& first = flow.tokens.front();
    const std::string seed = flow.id + "-" + first.id.value;
    GeneCode code{GeneId{"gene-" + seed},
                  GeneKind::State,
                  "lineage-" + seed,
                  "semantic-" + seed,
                  "constraint-" + seed,
                  "trajectory-" + seed};

    auto state_id = asking_star::core::statechain::make_state_gene_id(
        "", code.constraint_hash, code.trajectory_hash, "sheng-charge",
        first.protocol_root.digest, flow.id, seed);
    asking_star::core::statechain::StateGeneFragment state{
        state_id,
        std::nullopt,
        "charge-flow",
        "gene-code",
        code.constraint_hash,
        code.trajectory_hash,
        "sheng-charge",
        "yin=" + std::to_string(flow.total_yin_charge()),
        first.protocol_root.digest,
        asking_star::StateDiff{"compressed charge flow", {"charge"}, {}, {}},
        asking_star::RuntimeMode::AskingStar,
        seed,
        asking_star::now(),
        asking_star::core::statechain::GenerationStatus::Pending,
        "candidate compressed by YinCompress"};

    auto trace_id =
        asking_star::core::responsibility::make_responsibility_trace_id(
            "charge-pulse", "charge-scheduler", flow.id, "yin-compress", seed);
    asking_star::core::responsibility::ResponsibilityTrace trace{
        trace_id,
        "charge-pulse",
        {"charge-scheduler", "runtime"},
        {"yin-compress", "compress charge flow"},
        flow.id,
        asking_star::core::responsibility::ResponsibilityStatus::Scheduled,
        "candidate",
        "candidate responsibility by YinCompress"};

    return YinCompressResult{code, state, trace};
  }
};

}  // namespace asking_star::core::gene
