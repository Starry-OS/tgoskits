#pragma once

#include "asking_star/gcyy/gene_record.hpp"

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

namespace asking_star::v5 {

class ConcurrentGeneCache {
 public:
  GeneRecord get_or_insert(const std::string& key, GeneRecord record) {
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
  std::unordered_map<std::string, GeneRecord> records_;
};

}  // namespace asking_star::v5

