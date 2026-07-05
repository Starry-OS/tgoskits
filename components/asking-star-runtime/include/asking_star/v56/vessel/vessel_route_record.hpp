#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v56::vessel {

struct VesselRouteRecord {
  std::string route_id;
  std::string trace_id;
  std::string source_layer;
  std::string target_layer;
  std::uint64_t logical_order{0};

  [[nodiscard]] bool is_valid() const;
};

}  // namespace asking_star::v56::vessel

