#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/soil/kernel_request.hpp"
#include "asking_star/soil/kernel_result.hpp"
#include "asking_star/soil/soil_runtime.hpp"
#include "asking_star/v56/compat/v55_soil_adapter_bridge.hpp"

#include <string>

namespace asking_star::v56::soil {

enum class OSProfileKind {
  Mock,
  DryRun,
  Replay,
  LinuxUser,
  LinuxBaseline,
  StarryOSDryRun,
  BoardReal,
};

struct SoilDualChamberResult {
  asking_star::soil::KernelRequest request;
  asking_star::soil::KernelResult result;
  OSProfileKind os_profile{OSProfileKind::Mock};
  std::string adapter_mode{"Mock"};
  bool board_real_claim{false};

  [[nodiscard]] bool is_valid() const;
};

class AskingStarFacingSoilChamber {
 public:
  [[nodiscard]] asking_star::soil::KernelRequest make_request(
      const gcyy::DigitalCell& cell,
      asking_star::soil::OperationKind operation,
      std::string target_kind,
      std::string payload) const;

 private:
  asking_star::soil::SoilRuntime soil_;
};

class KernelFacingSoilChamber {
 public:
  [[nodiscard]] asking_star::soil::KernelResult execute(
      const asking_star::soil::KernelRequest& request) const;

 private:
  compat::V55SoilAdapterBridge adapter_;
};

class SoilDualChamber {
 public:
  [[nodiscard]] SoilDualChamberResult execute(
      const gcyy::DigitalCell& cell,
      OSProfileKind profile,
      std::string payload) const;

 private:
  AskingStarFacingSoilChamber asking_star_facing_;
  KernelFacingSoilChamber kernel_facing_;
};

[[nodiscard]] const char* to_string(OSProfileKind profile);

}  // namespace asking_star::v56::soil

