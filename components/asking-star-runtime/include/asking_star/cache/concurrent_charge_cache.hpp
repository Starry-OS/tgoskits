#pragma once

#include "asking_star/gcyy/charge_record.hpp"

#include <mutex>
#include <string>
#include <unordered_map>

namespace asking_star::v5 {

class ConcurrentChargeCache {
 public:
  ChargeRecord get_or_insert(const std::string& key, ChargeRecord record) {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto it = records_.find(key);
    if (it != records_.end()) {
      return it->second;
    }
    records_.emplace(key, record);
    return record;
  }

  std::size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return records_.size();
  }

 private:
  mutable std::mutex mutex_;
  std::unordered_map<std::string, ChargeRecord> records_;
};

}  // namespace asking_star::v5

