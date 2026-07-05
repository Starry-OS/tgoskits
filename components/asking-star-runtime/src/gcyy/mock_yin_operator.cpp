#include "asking_star/gcyy/mock_yin_operator.hpp"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace asking_star::gcyy {
namespace {

std::string hex64(std::uint64_t value) {
  std::ostringstream out;
  out << std::hex << value;
  return out.str();
}

}  // namespace

std::string make_mock_gene_hash(const DigitalSetFragment& fragment) {
  std::uint64_t hash = 1469598103934665603ULL;
  auto mix = [&hash](unsigned char value) {
    hash ^= value;
    hash *= 1099511628211ULL;
  };
  for (char value : fragment.fragment_id) {
    mix(static_cast<unsigned char>(value));
  }
  for (char value : fragment.star_tag) {
    mix(static_cast<unsigned char>(value));
  }
  for (auto value : fragment.payload) {
    mix(static_cast<unsigned char>(value));
  }
  return "gene-" + hex64(hash);
}

GcyyResult MockYinOperator::compress(const DigitalSetFragment& fragment,
                                     const ProjectionContext& context,
                                     GeneView& out_gene) const {
  auto fragment_result = fragment.validate();
  if (!fragment_result.ok()) {
    return fragment_result;
  }
  auto context_result = context.validate();
  if (!context_result.ok()) {
    return context_result;
  }
  const auto hash = make_mock_gene_hash(fragment);
  out_gene.gene_id = hash;
  out_gene.trace_id = fragment.trace_id;
  out_gene.state_hash = hash + "-state";
  out_gene.semantic_hash = hash + "-semantic";
  out_gene.star_tag = fragment.star_tag;
  out_gene.source_pointer = fragment.star_pointer;
  out_gene.compression_kind = "mock-yin";
  out_gene.dependencies = {fragment.fragment_id};
  out_gene.rule_version = context.rule_version.empty() ? "mock-rule-v1"
                                                       : context.rule_version;
  return out_gene.validate();
}

}  // namespace asking_star::gcyy
