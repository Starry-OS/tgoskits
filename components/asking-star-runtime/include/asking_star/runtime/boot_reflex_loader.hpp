#pragma once

#include "asking_star/charge/preset_charge_bank.hpp"
#include "asking_star/gene/boot_reflex_registry.hpp"

namespace asking_star::runtime {

class BootReflexLoader {
 public:
  void load_defaults(asking_star::gene::BootReflexRegistry& genes,
                     asking_star::charge::PresetChargeBank& charges) const;
};

}  // namespace asking_star::runtime
