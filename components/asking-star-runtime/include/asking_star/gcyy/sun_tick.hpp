#pragma once

#include <cstdint>
#include <string>

namespace asking_star::gcyy {

struct SunTick {
  std::uint64_t tick_id{0};
  std::uint64_t epoch{0};
  std::string trace_id;

  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

