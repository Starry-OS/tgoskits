#include "asking_star/gcyy/soil_runtime.hpp"

namespace asking_star::gcyy {

GcyyResult SoilRuntime::make_request(const DigitalCell& cell,
                                     KernelRequest& out_request) const {
  auto cell_result = cell.validate();
  if (!cell_result.ok()) {
    return cell_result;
  }
  out_request.request_id = "request-" + cell.cell_id;
  out_request.cell_id = cell.cell_id;
  out_request.trace_id = cell.trace_id;
  out_request.operation_kind = "mock.operation";
  out_request.payload_ref = cell.has_charge() ? cell.charge->payload_ref : "";
  out_request.dry_run = true;
  return out_request.is_valid()
             ? GcyyResult::success()
             : GcyyResult::failure(GcyyStatus::InvalidArgument,
                                   "invalid kernel request");
}

}  // namespace asking_star::gcyy

