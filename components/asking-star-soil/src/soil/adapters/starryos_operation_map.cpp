#include "asking_star/soil/adapters/starryos_operation_map.hpp"

namespace asking_star::soil::adapters {

StarryOSOperationMapping StarryOSOperationMap::map(
    OperationKind operation) const {
  switch (operation) {
    case OperationKind::LogWrite:
      return {operation, "StarryOS log / console write", true, true};
    case OperationKind::UartWrite:
      return {operation, "StarryOS UART write", true, true};
    case OperationKind::FileWrite:
      return {operation, "StarryOS file write or log fallback", true, true};
    case OperationKind::FileRead:
      return {operation, "StarryOS file read or unsupported", true, false};
    case OperationKind::DeviceIoctl:
      return {operation, "unsupported in first real version", false, false};
    case OperationKind::Noop:
      return {operation, "StarryOS noop", true, true};
    case OperationKind::Unknown:
      return {operation, "unknown", false, false};
  }
  return {OperationKind::Unknown, "unknown", false, false};
}

}  // namespace asking_star::soil::adapters

