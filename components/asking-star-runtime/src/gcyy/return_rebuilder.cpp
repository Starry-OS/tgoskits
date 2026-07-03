#include "asking_star/gcyy/return_rebuilder.hpp"

namespace asking_star::gcyy {

GcyyResult ReturnRebuilder::rebuild(
    const KernelResult& result, DigitalSetFragment& out_fragment) const {
  if (!result.is_valid()) {
    return GcyyResult::failure(result.status, "invalid kernel result");
  }
  out_fragment.fragment_id = "fragment-return-" + result.result_id;
  out_fragment.source_id = "return-rebuilder";
  out_fragment.trace_id = result.trace_id;
  out_fragment.star_tag = result.ok() ? "soil.result.ok" : "soil.result.error";
  out_fragment.star_pointer = "star://return/" + result.result_id;
  out_fragment.payload = {std::byte{'o'}, std::byte{'k'}};
  out_fragment.payload_hash = "hash-" + result.result_id;
  return out_fragment.validate();
}

}  // namespace asking_star::gcyy

