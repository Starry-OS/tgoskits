#pragma once

#include "asking_star/gene/boot_reflex_gene.hpp"

#include <optional>
#include <string>
#include <vector>

namespace asking_star::gene {

class BootReflexRegistry {
 public:
  [[nodiscard]] bool register_gene(BootReflexGene gene);
  [[nodiscard]] bool has_gene(const std::string& gene_id) const;
  [[nodiscard]] std::optional<BootReflexGene> find_gene(
      const std::string& gene_id) const;
  [[nodiscard]] std::vector<BootReflexGene> list_enabled() const;
  [[nodiscard]] std::size_t size() const;

 private:
  std::vector<BootReflexGene> genes_;
};

}  // namespace asking_star::gene
