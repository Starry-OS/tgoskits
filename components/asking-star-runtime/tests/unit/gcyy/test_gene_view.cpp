#include "asking_star/gcyy/gene_view.hpp"

#include <cassert>
#include <string>

int main() {
  asking_star::gcyy::GeneView gene;
  gene.gene_id = "gene-1";
  gene.trace_id = "trace-1";
  gene.state_hash = "state-hash";
  gene.semantic_hash = "semantic-hash";
  gene.star_tag = "input.text";
  gene.source_pointer = "star://input/1";
  gene.compression_kind = "mock-yin";
  gene.dependencies = {"fragment-1"};
  gene.rule_version = "rule-v1";

  assert(gene.has_trace());
  assert(gene.validate().ok());
  assert(gene.debug_dump().find("semantic-hash") != std::string::npos);

  gene.semantic_hash.clear();
  auto invalid = gene.validate();
  assert(!invalid.ok());
  assert(invalid.status == asking_star::gcyy::GcyyStatus::InvalidArgument);

  gene.semantic_hash = "semantic-hash";
  gene.trace_id.clear();
  auto missing_trace = gene.validate();
  assert(!missing_trace.ok());
  assert(missing_trace.status == asking_star::gcyy::GcyyStatus::MissingTraceId);

  return 0;
}

