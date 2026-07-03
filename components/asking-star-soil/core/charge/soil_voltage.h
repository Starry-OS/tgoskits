#pragma once

#include <string>

namespace asking_star::core::charge {

enum class Layer {
  Walker,
  Runtime,
  KernelSoil,
};

struct SoilVoltage {
  Layer layer{Layer::Runtime};
  double pressure{0.0};
  double resistance{0.0};
  double risk_tolerance{1.0};

  [[nodiscard]] bool is_valid() const {
    return pressure >= 0.0 && resistance >= 0.0 && risk_tolerance >= 0.0;
  }
};

struct GateBudget {
  double max_credit{0.0};
  double used_credit{0.0};

  [[nodiscard]] bool is_valid() const {
    return max_credit >= 0.0 && used_credit >= 0.0 &&
           used_credit <= max_credit;
  }

  [[nodiscard]] double remaining() const { return max_credit - used_credit; }
};

inline const char* to_string(Layer layer) {
  switch (layer) {
    case Layer::Walker:
      return "walker";
    case Layer::Runtime:
      return "runtime";
    case Layer::KernelSoil:
      return "kernel_soil";
  }
  return "runtime";
}

}  // namespace asking_star::core::charge
