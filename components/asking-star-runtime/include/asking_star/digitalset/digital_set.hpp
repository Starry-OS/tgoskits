#pragma once

#include "asking_star/digitalset/digital_set_fragment.hpp"
#include "asking_star/digitalset/digital_set_record.hpp"
#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/digitalset/digital_set_store.hpp"
#include "asking_star/digitalset/ref_resolver.hpp"

namespace asking_star::v5 {

struct DigitalSet {
  DigitalSetStore store;
};

}  // namespace asking_star::v5

