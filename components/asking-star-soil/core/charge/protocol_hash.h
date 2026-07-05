#pragma once

#include "core/charge/charge_protocol.h"

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace asking_star::core::charge {

struct ProtocolHash {
  ChargeProtocol protocol{ChargeProtocol::Force};
  std::string digest;

  [[nodiscard]] bool is_valid() const { return !digest.empty(); }
};

struct ProtocolHashSet {
  std::vector<ProtocolHash> hashes;

  [[nodiscard]] bool is_valid() const {
    if (hashes.empty()) {
      return false;
    }
    for (const auto& hash : hashes) {
      if (!hash.is_valid()) {
        return false;
      }
    }
    return true;
  }
};

struct ProtocolMerkleRoot {
  std::string digest;

  [[nodiscard]] bool is_valid() const { return !digest.empty(); }
};

inline std::string stable_protocol_digest(const std::string& input) {
  std::ostringstream out;
  out << std::hex << std::hash<std::string>{}(input);
  return out.str();
}

inline ProtocolHash make_protocol_hash(ChargeProtocol protocol,
                                       const std::string& payload) {
  return ProtocolHash{
      protocol,
      stable_protocol_digest(std::string{to_string(protocol)} + ":" + payload)};
}

inline ProtocolMerkleRoot make_protocol_merkle_root(
    const ProtocolHashSet& hash_set) {
  std::string joined;
  for (const auto& hash : hash_set.hashes) {
    joined += std::string{to_string(hash.protocol)} + ":" + hash.digest + ";";
  }
  return ProtocolMerkleRoot{stable_protocol_digest(joined)};
}

}  // namespace asking_star::core::charge
