#include "asking_star/digitalset/digital_set_fragment.hpp"
#include "asking_star/gcyy/digital_cell_record.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalSetFragment fragment;
  fragment.header.record_id = 9;
  fragment.header.type_tag = asking_star::v5::RecordTypeTag::Fragment;
  fragment.header.trace_id = "trace";
  asking_star::v5::DigitalCellRecord cell;
  cell.cell_id = fragment.header.record_id;
  cell.gene_ref.record_id = fragment.header.record_id;
  cell.gene_ref.expected_type_tag = asking_star::v5::RecordTypeTag::Gene;
  cell.gene_ref.expected_generation = fragment.header.generation;
  cell.gene_ref.trace_id = fragment.header.trace_id;
  assert(cell.cell_id == 9);
  assert(cell.gene_ref.expected_type_tag == asking_star::v5::RecordTypeTag::Gene);
  assert(!cell.charge_ref.has_value());
  return 0;
}
