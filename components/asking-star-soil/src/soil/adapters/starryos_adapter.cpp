#include "asking_star/soil/adapters/starryos_adapter.hpp"

namespace asking_star::soil::adapters {
namespace {

KernelResult unsupported(const KernelRequest& request,
                         const std::string& message) {
  return KernelResult{request.request_id,
                      request.trace_id,
                      SoilExecutionStatus::UnsupportedOperation,
                      "UnsupportedOperation",
                      "",
                      0,
                      message};
}

}  // namespace

StarryOSAdapter::StarryOSAdapter(StarryOSBuildConfig config)
    : config_(config) {}

const StarryOSBuildConfig& StarryOSAdapter::config() const { return config_; }

KernelResult StarryOSAdapter::execute(const KernelRequest& request) const {
  if (!request.is_valid()) {
    return KernelResult{request.request_id,
                        request.trace_id,
                        SoilExecutionStatus::InvalidRequest,
                        "InvalidRequest",
                        "",
                        0,
                        "invalid StarryOS adapter request"};
  }
  switch (config_.mode) {
    case StarryOSAdapterMode::DryRun:
      return dry_run(request);
    case StarryOSAdapterMode::HostMock:
      return host_mock(request);
    case StarryOSAdapterMode::BoardReal:
      return board_real(request);
  }
  return unsupported(request, "unknown StarryOS adapter mode");
}

KernelResult StarryOSAdapter::dry_run(const KernelRequest& request) const {
  const auto mapping = operation_map_.map(request.operation_kind);
  if (!mapping.dry_run_supported) {
    return unsupported(request, "StarryOS dry-run unsupported operation");
  }
  return KernelResult{request.request_id,
                      request.trace_id,
                      SoilExecutionStatus::Ok,
                      "",
                      "starryos-dryrun:" + request.payload,
                      1,
                      "StarryOS dry-run " + mapping.starryos_target};
}

KernelResult StarryOSAdapter::host_mock(const KernelRequest& request) const {
  MockKernelAdapter mock;
  auto result = mock.execute(request);
  if (result.ok()) {
    result.message = "StarryOS host-mock via MockKernelAdapter";
    result.payload = "starryos-hostmock:" + result.payload;
  }
  return result;
}

KernelResult StarryOSAdapter::board_real(const KernelRequest& request) const {
  const auto mapping = operation_map_.map(request.operation_kind);
  if (!mapping.first_real_supported) {
    return unsupported(request, "StarryOS BoardReal unsupported operation");
  }

  switch (request.operation_kind) {
    case OperationKind::LogWrite:
      return from_platform_result(request, platform_.write_log(request.payload));
    case OperationKind::UartWrite:
      return from_platform_result(request, platform_.write_uart(request.payload));
    case OperationKind::FileWrite:
      return from_platform_result(request,
                                  platform_.write_file(request.target_kind,
                                                       request.payload));
    case OperationKind::Noop:
      return KernelResult{request.request_id,
                          request.trace_id,
                          SoilExecutionStatus::Ok,
                          "",
                          "starryos-boardreal:noop",
                          0,
                          "StarryOS BoardReal noop"};
    case OperationKind::FileRead:
    case OperationKind::DeviceIoctl:
    case OperationKind::Unknown:
      return unsupported(request, "StarryOS BoardReal unsupported operation");
  }
  return unsupported(request, "unknown StarryOS BoardReal operation");
}

KernelResult StarryOSAdapter::from_platform_result(
    const KernelRequest& request,
    const StarryOSPlatformResult& platform_result) const {
  return KernelResult{request.request_id,
                      request.trace_id,
                      platform_result.status,
                      platform_result.ok() ? "" : "StarryOSPlatformError",
                      platform_result.payload,
                      platform_result.bytes_transferred,
                      platform_result.message};
}

}  // namespace asking_star::soil::adapters
