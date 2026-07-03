#pragma once

#include "asking_star/digitalset/digital_set_record.hpp"

#include <optional>
#include <unordered_map>

namespace asking_star::v5 {

class DigitalSetStore {
 public:
  DigitalSetRecord append(RecordTypeTag type_tag, std::string payload = {},
                          std::string trace_id = {});
  bool insert(DigitalSetRecord record);
  std::optional<DigitalSetRecord> find(std::uint64_t record_id) const;
  std::size_t size() const { return records_.size(); }

 private:
  std::uint64_t next_id_{1};
  std::unordered_map<std::uint64_t, DigitalSetRecord> records_;
};

}  // namespace asking_star::v5

