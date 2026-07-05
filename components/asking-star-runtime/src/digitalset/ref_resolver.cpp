#include "asking_star/digitalset/ref_resolver.hpp"

namespace asking_star::v5 {

RefResolution RefResolver::resolve(const DigitalSetRefRecord& ref) const {
  const auto record = store_.find(ref.record_id);
  if (!record) {
    return {false, std::nullopt, "record_not_found"};
  }
  if (record->header.type_tag != ref.expected_type_tag) {
    return {false, std::nullopt, "type_tag_mismatch"};
  }
  if (record->header.generation != ref.expected_generation) {
    return {false, std::nullopt, "generation_mismatch"};
  }
  if (!ref.hash_hint.empty() && record->header.fingerprint != ref.hash_hint) {
    return {false, std::nullopt, "hash_mismatch"};
  }
  return {true, record, {}};
}

}  // namespace asking_star::v5

