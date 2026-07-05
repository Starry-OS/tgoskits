#include "asking_star/gcyy/digital_set_fragment.hpp"

#include <sstream>

namespace asking_star::gcyy {

std::size_t DigitalSetFragment::payload_size() const { return payload.size(); }

bool DigitalSetFragment::has_trace() const { return !trace_id.empty(); }

GcyyResult DigitalSetFragment::validate() const {
  if (fragment_id.empty() || source_id.empty() || star_tag.empty() ||
      schema_version.empty()) {
    return GcyyResult::failure(GcyyStatus::InvalidArgument,
                               "fragment identity fields are required");
  }
  if (!has_trace()) {
    return GcyyResult::failure(GcyyStatus::MissingTraceId,
                               "fragment trace_id is required");
  }
  if (payload.empty()) {
    return GcyyResult::failure(GcyyStatus::MissingPayload,
                               "fragment payload is required");
  }
  return GcyyResult::success();
}

std::string DigitalSetFragment::debug_dump() const {
  std::ostringstream out;
  out << "DigitalSetFragment{id=" << fragment_id << ", source=" << source_id
      << ", trace=" << trace_id << ", tag=" << star_tag
      << ", payload_size=" << payload_size()
      << ", schema=" << schema_version << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

