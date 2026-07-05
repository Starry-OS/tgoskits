#include "asking_star/gcyy/gene_record.hpp"

#include <cassert>

int main() {
  asking_star::v5::GeneRecord record;
  record.gene_id = 1;
  record.trace_id = "trace";
  record.source_fragment_ref = {7, asking_star::v5::RecordTypeTag::Fragment};
  assert(record.source_fragment_ref.record_id == 7);
  return 0;
}
