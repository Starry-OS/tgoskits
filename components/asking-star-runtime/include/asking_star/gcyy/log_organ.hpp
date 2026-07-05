#pragma once

#include "asking_star/gcyy/organ_runtime.hpp"

namespace asking_star::gcyy {

class LogOrgan final : public OrganRuntime {
 public:
  explicit LogOrgan(std::string organ_id);
  [[nodiscard]] OrganResult execute(const DigitalCell& cell) const override;

 private:
  std::string organ_id_;
};

}  // namespace asking_star::gcyy

