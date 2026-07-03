#pragma once

#include "asking_star/v56/vessel/vessel_gate_record.hpp"
#include "asking_star/v56/vessel/vessel_packet_record.hpp"

namespace asking_star::v56::vessel {

class VesselPolicy {
 public:
  [[nodiscard]] bool allows(const VesselPacketRecord& packet,
                            const VesselGateRecord& gate) const;
};

}  // namespace asking_star::v56::vessel

