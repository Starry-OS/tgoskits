#include "asking_star/soil/soil_execution_status.hpp"

namespace asking_star::soil {

const char* to_string(SoilExecutionStatus status) {
  switch (status) {
    case SoilExecutionStatus::Ok:
      return "Ok";
    case SoilExecutionStatus::Rejected:
      return "Rejected";
    case SoilExecutionStatus::InvalidRequest:
      return "InvalidRequest";
    case SoilExecutionStatus::UnsupportedOperation:
      return "UnsupportedOperation";
    case SoilExecutionStatus::Timeout:
      return "Timeout";
    case SoilExecutionStatus::AdapterFailed:
      return "AdapterFailed";
    case SoilExecutionStatus::KernelFailed:
      return "KernelFailed";
    case SoilExecutionStatus::RebuildFailed:
      return "RebuildFailed";
    case SoilExecutionStatus::UnknownError:
      return "UnknownError";
  }
  return "UnknownError";
}

bool is_success(SoilExecutionStatus status) {
  return status == SoilExecutionStatus::Ok;
}

const char* to_string(OperationKind operation) {
  switch (operation) {
    case OperationKind::LogWrite:
      return "LogWrite";
    case OperationKind::UartWrite:
      return "UartWrite";
    case OperationKind::FileWrite:
      return "FileWrite";
    case OperationKind::FileRead:
      return "FileRead";
    case OperationKind::DeviceIoctl:
      return "DeviceIoctl";
    case OperationKind::Noop:
      return "Noop";
    case OperationKind::Unknown:
      return "Unknown";
  }
  return "Unknown";
}

}  // namespace asking_star::soil

