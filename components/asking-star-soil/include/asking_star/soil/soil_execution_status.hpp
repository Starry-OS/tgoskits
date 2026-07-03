#pragma once

#include <string>

namespace asking_star::soil {

enum class SoilExecutionStatus {
  Ok,
  Rejected,
  InvalidRequest,
  UnsupportedOperation,
  Timeout,
  AdapterFailed,
  KernelFailed,
  RebuildFailed,
  UnknownError,
};

[[nodiscard]] const char* to_string(SoilExecutionStatus status);
[[nodiscard]] bool is_success(SoilExecutionStatus status);

struct SoilRequestId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};

enum class OperationKind {
  LogWrite,
  UartWrite,
  FileWrite,
  FileRead,
  DeviceIoctl,
  Noop,
  Unknown,
};

[[nodiscard]] const char* to_string(OperationKind operation);

}  // namespace asking_star::soil

