#include "asking_star/gcyy/charge_record.hpp"

#include <cassert>

int main() {
  asking_star::v5::ChargeRecord record;
  record.charge_id = 1;
  record.gene_ref = {2, asking_star::v5::RecordTypeTag::Gene};
  record.execution_intent = "execute";
  assert(record.ttl_ticks == 1);
  assert(record.gene_ref.record_id == 2);
  return 0;
}
