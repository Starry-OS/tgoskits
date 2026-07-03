#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/soil/abi_packet.hpp"
#include "asking_star/soil/kernel_request.hpp"

namespace asking_star::soil {

class SoilRuntime {
 public:
  [[nodiscard]] KernelRequest make_request(
      const asking_star::gcyy::DigitalCell& cell,
      OperationKind operation = OperationKind::LogWrite,
      std::string target_kind = "mock.log",
      std::string payload = "mock payload") const;

  [[nodiscard]] AbiPacket make_abi_packet(const KernelRequest& request) const;
};

}  // namespace asking_star::soil

