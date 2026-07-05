#include "asking_star/soil/abi_packet.hpp"

#include <cstddef>

namespace asking_star::soil {

AbiPacket make_abi_packet(const KernelRequest& request) {
  std::vector<std::byte> bytes;
  bytes.reserve(request.payload.size());
  for (char ch : request.payload) {
    bytes.push_back(static_cast<std::byte>(static_cast<unsigned char>(ch)));
  }
  return AbiPacket{request.request_id,
                   request.trace_id,
                   request.operation_kind,
                   request.target_kind,
                   MemoryBufferView{"payload-" + request.request_id.value,
                                    std::move(bytes), true},
                   SyscallPlan{request.operation_kind,
                               "plan-" + request.request_id.value, true}};
}

}  // namespace asking_star::soil

