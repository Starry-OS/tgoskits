#include "asking_star/soil/return_rebuilder.hpp"

#include <cstddef>

namespace asking_star::soil {

SoilExecutionStatus ReturnRebuilder::rebuild(
    const KernelResult& result,
    asking_star::gcyy::DigitalSetFragment& out_fragment) const {
  if (!result.is_valid()) {
    return SoilExecutionStatus::RebuildFailed;
  }
  out_fragment.fragment_id = "soil-return-" + result.request_id.value;
  out_fragment.source_id = "soil-return-rebuilder";
  out_fragment.trace_id = result.trace_id;
  out_fragment.star_tag = result.ok() ? "soil.kernel_result.ok"
                                      : "soil.kernel_result.error";
  out_fragment.star_pointer = "star://soil/result/" + result.request_id.value;
  const auto payload = result.ok() ? result.payload : result.error_code;
  out_fragment.payload.clear();
  out_fragment.payload.reserve(payload.size());
  for (char ch : payload) {
    out_fragment.payload.push_back(
        static_cast<std::byte>(static_cast<unsigned char>(ch)));
  }
  if (out_fragment.payload.empty()) {
    out_fragment.payload.push_back(std::byte{'0'});
  }
  out_fragment.payload_hash = "soil-result-" + result.request_id.value;
  return out_fragment.validate().ok() ? SoilExecutionStatus::Ok
                                      : SoilExecutionStatus::RebuildFailed;
}

}  // namespace asking_star::soil

