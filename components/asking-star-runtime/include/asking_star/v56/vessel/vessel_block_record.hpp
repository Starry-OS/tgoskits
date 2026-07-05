#pragma once

#include <string>

namespace asking_star::v56::vessel {

struct VesselBlockRecord {
  std::string block_id;
  std::string trace_id;
  std::string packet_id;
  std::string gate_id;
  std::string reason;

  [[nodiscard]] bool is_valid() const;
};

}  // namespace asking_star::v56::vessel

