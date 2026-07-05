#pragma once

#include "asking_star/charge/preset_charge.hpp"

#include <optional>
#include <string>
#include <vector>

namespace asking_star::charge {

class PresetChargeBank {
 public:
  [[nodiscard]] bool register_charge(PresetCharge charge);
  [[nodiscard]] bool has_charge(const std::string& charge_id) const;
  [[nodiscard]] std::optional<PresetCharge> find_charge(
      const std::string& charge_id) const;
  [[nodiscard]] std::optional<PresetCharge> find_by_gene(
      const std::string& gene_id) const;
  [[nodiscard]] std::vector<PresetCharge> list() const;
  [[nodiscard]] std::size_t size() const;

 private:
  std::vector<PresetCharge> charges_;
};

}  // namespace asking_star::charge
