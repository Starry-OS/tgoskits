#pragma once

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace asking_star::core::charge {

enum class ChargeProtocol {
  Force = 0,
  Law = 1,
  Wisdom = 2,
  Hua = 3,
  Yun = 4,
  Meng = 5,
};

enum class ChargeKind {
  Light,
  Wave,
  Dual,
};

class ProtocolBitMask {
 public:
  ProtocolBitMask() = default;

  explicit ProtocolBitMask(std::vector<ChargeProtocol> protocols) {
    for (const auto protocol : protocols) {
      add(protocol);
    }
  }

  void add(ChargeProtocol protocol) {
    bits_ |= (static_cast<std::uint8_t>(1U)
              << static_cast<std::uint8_t>(protocol));
  }

  [[nodiscard]] bool contains(ChargeProtocol protocol) const {
    return (bits_ & (static_cast<std::uint8_t>(1U)
                     << static_cast<std::uint8_t>(protocol))) != 0;
  }

  [[nodiscard]] bool is_valid() const { return bits_ != 0; }

  [[nodiscard]] std::uint8_t value() const { return bits_; }

 private:
  std::uint8_t bits_{0};
};

struct ProtocolWeightVector {
  std::array<double, 6> weights{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  [[nodiscard]] bool is_valid() const {
    bool has_weight = false;
    for (const auto weight : weights) {
      if (weight < 0.0) {
        return false;
      }
      has_weight = has_weight || weight > 0.0;
    }
    return has_weight;
  }

  [[nodiscard]] double get(ChargeProtocol protocol) const {
    return weights[static_cast<std::size_t>(protocol)];
  }

  [[nodiscard]] double yin_bias() const {
    return get(ChargeProtocol::Law) + get(ChargeProtocol::Wisdom) +
           get(ChargeProtocol::Meng);
  }

  [[nodiscard]] double yang_bias() const {
    return get(ChargeProtocol::Force) + get(ChargeProtocol::Hua) +
           get(ChargeProtocol::Yun);
  }
};

inline const char* to_string(ChargeProtocol protocol) {
  switch (protocol) {
    case ChargeProtocol::Force:
      return "force";
    case ChargeProtocol::Law:
      return "law";
    case ChargeProtocol::Wisdom:
      return "wisdom";
    case ChargeProtocol::Hua:
      return "hua";
    case ChargeProtocol::Yun:
      return "yun";
    case ChargeProtocol::Meng:
      return "meng";
  }
  return "force";
}

inline const char* to_string(ChargeKind kind) {
  switch (kind) {
    case ChargeKind::Light:
      return "light";
    case ChargeKind::Wave:
      return "wave";
    case ChargeKind::Dual:
      return "dual";
  }
  return "light";
}

}  // namespace asking_star::core::charge
