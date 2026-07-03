#include "asking_star/gcyy/digital_cell_view.hpp"

#include <cassert>

int main() {
  asking_star::v5::DigitalCellView view;
  view.record.cell_id = 1;
  view.record.gene_ref = {2, asking_star::v5::RecordTypeTag::Gene};
  view.record.charge_ref = asking_star::v5::DigitalSetRefRecord{
      3, asking_star::v5::RecordTypeTag::Charge};
  assert(view.record.charge_ref.has_value());
  return 0;
}

