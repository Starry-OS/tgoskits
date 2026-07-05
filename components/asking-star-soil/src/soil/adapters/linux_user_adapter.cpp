#include "asking_star/soil/adapters/linux_user_adapter.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace asking_star::soil::adapters {
namespace {

KernelResult rejected(const KernelRequest& request, SoilExecutionStatus status,
                      const std::string& code, const std::string& message) {
  return KernelResult{request.request_id, request.trace_id, status, code, "", 0,
                      message};
}

}  // namespace

LinuxUserAdapter::LinuxUserAdapter(std::filesystem::path runtime_tmp_dir)
    : runtime_tmp_dir_(std::move(runtime_tmp_dir)) {}

const std::filesystem::path& LinuxUserAdapter::runtime_tmp_dir() const {
  return runtime_tmp_dir_;
}

bool LinuxUserAdapter::is_safe_relative_path(const std::string& path) const {
  if (path.empty() || path == "CMakeLists.txt") {
    return false;
  }
  const std::filesystem::path candidate{path};
  if (candidate.is_absolute()) {
    return false;
  }
  for (const auto& part : candidate) {
    if (part == ".." || part == "." || part.empty()) {
      return false;
    }
  }
  return candidate.filename() == candidate;
}

std::filesystem::path LinuxUserAdapter::resolve_safe_path(
    const std::string& path) const {
  return runtime_tmp_dir_ / std::filesystem::path{path}.filename();
}

KernelResult LinuxUserAdapter::execute(const KernelRequest& request) const {
  if (!request.is_valid()) {
    return rejected(request, SoilExecutionStatus::InvalidRequest,
                    "InvalidRequest", "invalid linux user request");
  }

  switch (request.operation_kind) {
    case OperationKind::LogWrite:
      std::cout << request.payload;
      return KernelResult{request.request_id, request.trace_id,
                          SoilExecutionStatus::Ok, "", request.payload, 1,
                          "linux user log write ok"};
    case OperationKind::Noop:
      return KernelResult{request.request_id, request.trace_id,
                          SoilExecutionStatus::Ok, "", "noop", 0,
                          "linux user noop ok"};
    case OperationKind::FileWrite: {
      if (!is_safe_relative_path(request.target_kind)) {
        return rejected(request, SoilExecutionStatus::Rejected, "UnsafePath",
                        "file write path rejected");
      }
      std::filesystem::create_directories(runtime_tmp_dir_);
      std::ofstream out(resolve_safe_path(request.target_kind),
                        std::ios::binary | std::ios::trunc);
      if (!out) {
        return rejected(request, SoilExecutionStatus::AdapterFailed,
                        "FileWriteFailed", "failed to open runtime tmp file");
      }
      out << request.payload;
      return KernelResult{request.request_id, request.trace_id,
                          SoilExecutionStatus::Ok, "", request.payload, 1,
                          "linux user file write ok"};
    }
    case OperationKind::FileRead: {
      if (!is_safe_relative_path(request.target_kind)) {
        return rejected(request, SoilExecutionStatus::Rejected, "UnsafePath",
                        "file read path rejected");
      }
      std::ifstream in(resolve_safe_path(request.target_kind), std::ios::binary);
      if (!in) {
        return rejected(request, SoilExecutionStatus::AdapterFailed,
                        "FileReadFailed", "failed to read runtime tmp file");
      }
      std::ostringstream buffer;
      buffer << in.rdbuf();
      return KernelResult{request.request_id, request.trace_id,
                          SoilExecutionStatus::Ok, "", buffer.str(), 1,
                          "linux user file read ok"};
    }
    case OperationKind::UartWrite:
    case OperationKind::DeviceIoctl:
    case OperationKind::Unknown:
      return rejected(request, SoilExecutionStatus::UnsupportedOperation,
                      "UnsupportedOperation",
                      "linux user adapter does not support this operation");
  }
  return rejected(request, SoilExecutionStatus::UnknownError, "UnknownError",
                  "unreachable linux user adapter branch");
}

}  // namespace asking_star::soil::adapters
