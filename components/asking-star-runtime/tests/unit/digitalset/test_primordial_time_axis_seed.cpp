#include "asking_star/digitalset/primordial_digital_set.hpp"

#include <cassert>

int main() {
  asking_star::v5::PrimordialDigitalSet primordial;
  primordial.decode_rules.push_back("bit-root");
  primordial.star_fast_table.push_back("star-entry");
  primordial.time_axis_seed = asking_star::v5::TimeAxisSeedRecord{
      .epoch0 = 1, .tick0 = 2, .timeline_record_base = 10};
  assert(asking_star::v5::has_time_axis_seed(primordial));
  assert(primordial.time_axis_seed->timeline_record_base == 10);
  return 0;
}

