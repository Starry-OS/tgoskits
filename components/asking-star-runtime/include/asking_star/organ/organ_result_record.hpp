#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v5 {

struct OrganResultRecord {
  std::string organ_id;
  std::uint64_t cell_id{0};
  std::string trace_id;
  bool ok{true};
  std::string message;
};

}  // namespace asking_star::v5

