#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/digitalset/digital_set_store.hpp"

#include <optional>
#include <string>

namespace asking_star::v5 {

struct RefResolution {
  bool ok{false};
  std::optional<DigitalSetRecord> record;
  std::string error;
};

class RefResolver {
 public:
  explicit RefResolver(const DigitalSetStore& store) : store_(store) {}
  RefResolution resolve(const DigitalSetRefRecord& ref) const;

 private:
  const DigitalSetStore& store_;
};

}  // namespace asking_star::v5

