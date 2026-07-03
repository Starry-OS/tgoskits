#pragma once

#include "core/boot/boot_artifact_index.h"
#include "core/charge/charge_token.h"
#include "core/kernelsoil/soil_request.h"

#include <string>
#include <vector>

namespace asking_star::core::boot {

struct BootIntent {
  std::string id;
  std::string artifact_id;
  std::string reason;
  bool allow_real_qemu{true};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && !reason.empty();
  }
};

struct BootPlan {
  std::string id;
  BootIntent intent;
  StarryOSArtifact artifact;
  asking_star::core::charge::ChargeToken gate_token;
  asking_star::core::kernelsoil::SoilRequest soil_request;
  std::vector<std::string> trace;

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && intent.is_valid() && artifact.is_valid() &&
           gate_token.is_valid() && soil_request.is_valid();
  }
};

struct BootResult {
  std::string boot_id;
  std::string status;
  std::string terminal_endpoint;
  bool qemu_started{false};
  bool terminal_attached{false};
  bool shell_stable{false};
  bool authoritative_fact_written{false};
  std::vector<std::string> trace;

  [[nodiscard]] bool is_valid() const {
    return !boot_id.empty() && !status.empty();
  }
};

}  // namespace asking_star::core::boot
