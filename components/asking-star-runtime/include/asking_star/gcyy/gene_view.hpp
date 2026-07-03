#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <string>
#include <vector>

namespace asking_star::gcyy {

// GeneView is the compressed, indexable state view produced by Yin.
struct GeneView {
  std::string gene_id;
  std::string trace_id;
  std::string schema_version{"gcyy.gene.v1"};
  std::string state_hash;
  std::string semantic_hash;
  std::string star_tag;
  std::string source_pointer;
  std::string compression_kind;
  std::vector<std::string> dependencies;
  std::string rule_version;

  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] GcyyResult validate() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

