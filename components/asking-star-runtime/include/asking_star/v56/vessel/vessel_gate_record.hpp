#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v56::vessel {

struct VesselGateRecord {
  std::string gate_id;
  std::string trace_id;
  std::uint32_t required_permission_mask{0};
  bool enabled{true};
  std::string reason;

  [[nodiscard]] bool is_valid() const;
};

}  // namespace asking_star::v56::vessel

