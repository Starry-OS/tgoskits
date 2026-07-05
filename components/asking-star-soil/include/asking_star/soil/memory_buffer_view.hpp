#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace asking_star::soil {

struct MemoryBufferView {
  std::string buffer_id;
  std::vector<std::byte> bytes;
  bool read_only{true};

  [[nodiscard]] bool is_valid() const {
    return !buffer_id.empty() && !bytes.empty();
  }
  [[nodiscard]] std::size_t size() const { return bytes.size(); }
};

}  // namespace asking_star::soil

