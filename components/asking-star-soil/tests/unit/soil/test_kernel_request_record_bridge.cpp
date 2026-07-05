#include "asking_star/soil/kernel_request_record.hpp"

#include <cassert>

int main() {
  asking_star::v5::KernelRequestRecord record;
  record.cell_ref.record_id = 7;
  record.cell_ref.trace_id = "trace";
  record.origin_gene_id = "gene-7";
  record.origin_charge_id = "charge-7";
  record.payload = "hello";
  const auto request = asking_star::v5::to_kernel_request(record);
  assert(request.cell_id == "7");
  assert(request.trace_id == "trace");
  assert(request.origin_gene_id == "gene-7");
  assert(request.origin_charge_id == "charge-7");
  assert(request.payload == "hello");
  assert(request.is_valid());
  return 0;
}
