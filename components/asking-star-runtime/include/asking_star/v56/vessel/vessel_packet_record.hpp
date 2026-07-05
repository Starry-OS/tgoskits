#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace asking_star::v56::vessel {

enum class VesselPacketStatus {
  Ready,
  Blocked,
  Recovered,
};

struct VesselPacketRecord {
  std::string packet_id;
  std::string trace_id;
  std::string route_id;
  std::uint32_t permission_mask{0};
  VesselPacketStatus status{VesselPacketStatus::Ready};
  std::optional<v5::DigitalSetRefRecord> fragment_ref;
  std::optional<v5::DigitalSetRefRecord> app_intent_ref;
  std::optional<v5::DigitalSetRefRecord> app_result_ref;
  std::optional<v5::DigitalSetRefRecord> gene_ref;
  std::optional<v5::DigitalSetRefRecord> charge_ref;
  std::optional<v5::DigitalSetRefRecord> cell_ref;
  std::optional<v5::DigitalSetRefRecord> kernel_request_ref;
  std::optional<v5::DigitalSetRefRecord> kernel_result_ref;

  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] bool has_any_ref() const;
  [[nodiscard]] bool is_valid() const;
};

[[nodiscard]] const char* to_string(VesselPacketStatus status);

}  // namespace asking_star::v56::vessel

