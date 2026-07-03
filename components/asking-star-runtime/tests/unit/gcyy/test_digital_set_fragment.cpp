#include "asking_star/gcyy/digital_set_fragment.hpp"

#include <cassert>
#include <cstddef>
#include <string>

namespace {

asking_star::gcyy::DigitalSetFragment make_fragment() {
  return asking_star::gcyy::DigitalSetFragment{
      "fragment-1",
      "walker-runtime",
      "trace-1",
      "input.text",
      "star://input/1",
      {std::byte{'a'}, std::byte{'s'}},
      "hash-fragment-1",
      "gcyy.fragment.v1"};
}

}  // namespace

int main() {
  auto fragment = make_fragment();
  assert(fragment.payload_size() == 2);
  assert(fragment.has_trace());
  assert(fragment.validate().ok());
  assert(fragment.debug_dump().find("trace-1") != std::string::npos);

  fragment.trace_id.clear();
  auto missing_trace = fragment.validate();
  assert(!missing_trace.ok());
  assert(missing_trace.status == asking_star::gcyy::GcyyStatus::MissingTraceId);

  fragment = make_fragment();
  fragment.payload.clear();
  auto missing_payload = fragment.validate();
  assert(!missing_payload.ok());
  assert(missing_payload.status ==
         asking_star::gcyy::GcyyStatus::MissingPayload);

  return 0;
}

