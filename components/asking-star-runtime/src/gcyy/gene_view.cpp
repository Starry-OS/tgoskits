#include "asking_star/gcyy/gene_view.hpp"

#include <sstream>

namespace asking_star::gcyy {

bool GeneView::has_trace() const { return !trace_id.empty(); }

GcyyResult GeneView::validate() const {
  if (gene_id.empty() || state_hash.empty() || semantic_hash.empty() ||
      schema_version.empty()) {
    return GcyyResult::failure(GcyyStatus::InvalidArgument,
                               "gene identity and hash fields are required");
  }
  if (!has_trace()) {
    return GcyyResult::failure(GcyyStatus::MissingTraceId,
                               "gene trace_id is required");
  }
  return GcyyResult::success();
}

std::string GeneView::debug_dump() const {
  std::ostringstream out;
  out << "GeneView{id=" << gene_id << ", trace=" << trace_id
      << ", state_hash=" << state_hash
      << ", semantic_hash=" << semantic_hash << ", tag=" << star_tag
      << ", compression=" << compression_kind << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

