#pragma once

#include "asking_star/v56/vessel/vessel_block_record.hpp"
#include "asking_star/v56/vessel/vessel_gate_record.hpp"
#include "asking_star/v56/vessel/vessel_packet_record.hpp"
#include "asking_star/v56/vessel/vessel_policy.hpp"
#include "asking_star/v56/vessel/vessel_recovery_record.hpp"
#include "asking_star/v56/vessel/vessel_route_record.hpp"
#include "asking_star/v56/vessel/vessel_tap_record.hpp"

#include <optional>
#include <string>

namespace asking_star::v56::vessel {

struct VesselBusResult {
  VesselPacketRecord packet;
  std::optional<VesselBlockRecord> block;

  [[nodiscard]] bool ok() const;
};

class VesselBus {
 public:
  [[nodiscard]] VesselBusResult transport(
      VesselPacketRecord packet,
      const VesselRouteRecord& route,
      const VesselGateRecord& gate) const;

  [[nodiscard]] VesselTapRecord tap(const VesselPacketRecord& packet,
                                    std::string observer_kind) const;

  [[nodiscard]] VesselRecoveryRecord recover(
      const VesselBlockRecord& block,
      const VesselPacketRecord& recovered_packet,
      std::string reason) const;

 private:
  VesselPolicy policy_;
};

}  // namespace asking_star::v56::vessel

