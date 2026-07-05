#include "asking_star/digitalset/digital_set_store.hpp"

#include <utility>

namespace asking_star::v5 {

DigitalSetRecord DigitalSetStore::append(RecordTypeTag type_tag,
                                         std::string payload,
                                         std::string trace_id) {
  DigitalSetRecord record;
  record.header.record_id = next_id_++;
  record.header.type_tag = type_tag;
  record.header.version = 1;
  record.header.generation = 1;
  record.header.trace_id = std::move(trace_id);
  record.header.fingerprint = record.header.trace_id + ":" + payload;
  record.payload = std::move(payload);
  records_.emplace(record.header.record_id, record);
  return record;
}

bool DigitalSetStore::insert(DigitalSetRecord record) {
  const auto record_id = record.header.record_id;
  if (record_id == 0 || records_.contains(record_id)) {
    return false;
  }
  if (record_id >= next_id_) {
    next_id_ = record_id + 1;
  }
  records_.emplace(record_id, std::move(record));
  return true;
}

std::optional<DigitalSetRecord> DigitalSetStore::find(
    std::uint64_t record_id) const {
  const auto it = records_.find(record_id);
  if (it == records_.end()) {
    return std::nullopt;
  }
  return it->second;
}

}  // namespace asking_star::v5

