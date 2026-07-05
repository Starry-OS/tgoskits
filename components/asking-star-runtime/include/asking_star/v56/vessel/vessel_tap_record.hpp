#pragma once

#include <string>

namespace asking_star::v56::vessel {

struct VesselTapRecord {
  std::string tap_id;
  std::string trace_id;
  std::string packet_id;
  std::string observer_kind;

  [[nodiscard]] bool is_valid() const;
};

}  // namespace asking_star::v56::vessel

