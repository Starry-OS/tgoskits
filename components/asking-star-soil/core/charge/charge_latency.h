#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::core::charge {

enum class LatencyStage {
  Router,
  TreeQueue,
  ValveDecision,
  KernelSoilDispatch,
  NpuSubmit,
  IrqFeedback,
  ControlLoop,
};

struct ChargeLatencySample {
  LatencyStage stage{LatencyStage::Router};
  std::uint64_t latency_us{0};
  std::string trace;

  [[nodiscard]] bool is_valid() const { return !trace.empty(); }
};

struct ChargeLatencyBudget {
  std::uint64_t control_loop_budget_us{50000};
  std::uint64_t jitter_budget_us{5000};

  [[nodiscard]] bool is_valid() const {
    return control_loop_budget_us > 0 && jitter_budget_us > 0 &&
           jitter_budget_us < control_loop_budget_us;
  }
};

class ChargeLatencyTrace {
 public:
  void record(ChargeLatencySample sample) { samples_.push_back(std::move(sample)); }

  [[nodiscard]] bool fits_20fps_guard(
      const ChargeLatencyBudget& budget = ChargeLatencyBudget{}) const {
    if (!budget.is_valid()) {
      return false;
    }
    std::uint64_t total = 0;
    for (const auto& sample : samples_) {
      if (!sample.is_valid()) {
        return false;
      }
      total += sample.latency_us;
    }
    return total + budget.jitter_budget_us <= budget.control_loop_budget_us;
  }

  [[nodiscard]] bool requires_fast_path(
      const ChargeLatencyBudget& budget = ChargeLatencyBudget{}) const {
    return !fits_20fps_guard(budget);
  }

  [[nodiscard]] bool claims_hard_realtime() const { return false; }

 private:
  std::vector<ChargeLatencySample> samples_;
};

}  // namespace asking_star::core::charge
