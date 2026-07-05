#pragma once

#include <string>

namespace asking_star::v56::vessel {

struct VesselRecoveryRecord {
  std::string recovery_id;
  std::string trace_id;
  std::string blocked_packet_id;
  std::string recovered_packet_id;
  std::string reason;

  [[nodiscard]] bool is_valid() const;
};

}  // namespace asking_star::v56::vessel

