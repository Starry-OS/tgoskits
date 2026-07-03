#pragma once

#include "asking_star/v55/chamber_pouch.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v55 {

struct ChamberReflexGeneRecord {
  std::uint64_t reflex_gene_id{0};
  std::uint64_t source_pouch_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  double confidence{0.0};
  std::string preset_payload;
};

struct ChamberPresetChargeRecord {
  std::uint64_t preset_charge_id{0};
  std::uint64_t reflex_gene_id{0};
  std::string payload;
  bool requires_sun_admission{true};
};

class ReflexGeneBank {
 public:
  [[nodiscard]] ChamberReflexGeneRecord compress(
      const ChamberPouchRecord& pouch) {
    ChamberReflexGeneRecord gene;
    gene.reflex_gene_id = pouch.pouch_id + 1000;
    gene.source_pouch_id = pouch.pouch_id;
    gene.adapter_mode = pouch.adapter_mode;
    gene.confidence = pouch.reflex_candidate ? 0.6 : 0.1;
    gene.preset_payload = pouch.output;
    genes_.push_back(gene);
    return gene;
  }

  [[nodiscard]] ChamberPresetChargeRecord expand(
      const ChamberReflexGeneRecord& gene) const {
    ChamberPresetChargeRecord preset;
    preset.preset_charge_id = gene.reflex_gene_id + 1000;
    preset.reflex_gene_id = gene.reflex_gene_id;
    preset.payload = gene.preset_payload;
    preset.requires_sun_admission = true;
    return preset;
  }

  [[nodiscard]] const std::vector<ChamberReflexGeneRecord>& genes() const {
    return genes_;
  }

 private:
  std::vector<ChamberReflexGeneRecord> genes_;
};

}  // namespace asking_star::v55
