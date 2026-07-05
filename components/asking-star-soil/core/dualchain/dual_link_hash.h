#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace asking_star::core::dualchain {

struct HashDigest {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }

  friend bool operator==(const HashDigest& lhs, const HashDigest& rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const HashDigest& lhs, const HashDigest& rhs) {
    return !(lhs == rhs);
  }
};

class StableHashInput {
 public:
  StableHashInput& add(std::string_view part) {
    parts_.emplace_back(part);
    return *this;
  }

  [[nodiscard]] const std::vector<std::string>& parts() const {
    return parts_;
  }

 private:
  std::vector<std::string> parts_;
};

inline std::string fnv1a_64_hex(const std::vector<std::string>& parts) {
  constexpr std::uint64_t offset_basis = 14695981039346656037ULL;
  constexpr std::uint64_t prime = 1099511628211ULL;

  std::uint64_t hash = offset_basis;
  for (const auto& part : parts) {
    for (unsigned char byte : part) {
      hash ^= byte;
      hash *= prime;
    }
    hash ^= 0x1FULL;
    hash *= prime;
  }

  std::ostringstream out;
  out << std::hex << std::setw(16) << std::setfill('0') << hash;
  return out.str();
}

inline HashDigest make_hash_digest(const StableHashInput& input) {
  return HashDigest{fnv1a_64_hex(input.parts())};
}

struct DualLinkHash {
  HashDigest digest;

  [[nodiscard]] bool is_valid() const { return digest.is_valid(); }

  friend bool operator==(const DualLinkHash& lhs, const DualLinkHash& rhs) {
    return lhs.digest == rhs.digest;
  }
};

inline DualLinkHash make_dual_link_hash(std::string_view state_gene_id,
                                        std::string_view trace_id,
                                        std::string_view reason,
                                        std::string_view event_id) {
  StableHashInput input;
  input.add("dual-link")
      .add(state_gene_id)
      .add(trace_id)
      .add(reason)
      .add(event_id);
  return DualLinkHash{make_hash_digest(input)};
}

}  // namespace asking_star::core::dualchain
