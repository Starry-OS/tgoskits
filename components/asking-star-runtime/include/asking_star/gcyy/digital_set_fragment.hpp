#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace asking_star::gcyy {

// DigitalSetFragment is an uninterpreted fact slice entering GCYY.
struct DigitalSetFragment {
  std::string fragment_id;
  std::string source_id;
  std::string trace_id;
  std::string star_tag;
  std::string star_pointer;
  std::vector<std::byte> payload;
  std::string payload_hash;
  std::string schema_version{"gcyy.fragment.v1"};

  [[nodiscard]] std::size_t payload_size() const;
  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] GcyyResult validate() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

