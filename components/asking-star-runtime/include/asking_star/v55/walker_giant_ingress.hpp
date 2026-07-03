#pragma once

#include "asking_star/digitalset/digital_set_fragment.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

using v5::DigitalSetFragment;
using v5::DigitalSetRecord;
using v5::DigitalSetRecordHeader;
using v5::RecordTypeTag;

enum class WalkerInputKind {
  Command,
  NaturalLanguage,
  UiEvent,
  Sensor,
  AiResult,
  Replay,
  ExternalApp,
};

struct WalkerInputRecord {
  std::uint64_t input_id{0};
  WalkerInputKind kind{WalkerInputKind::Command};
  std::string payload;
  std::string trace_id;
};

struct AppIntentRecord {
  std::uint64_t intent_id{0};
  WalkerInputKind source_kind{WalkerInputKind::Command};
  std::string normalized_payload;
  std::string trace_id;
};

class WalkerIngress {
 public:
  [[nodiscard]] DigitalSetFragment accept(const WalkerInputRecord& input) const {
    DigitalSetFragment fragment;
    fragment.header.record_id = input.input_id;
    fragment.header.type_tag = RecordTypeTag::Fragment;
    fragment.header.trace_id = input.trace_id;
    fragment.header.fingerprint = "walker-ingress";

    DigitalSetRecord record;
    record.header.record_id = input.input_id + 1000;
    record.header.type_tag = RecordTypeTag::Payload;
    record.header.trace_id = input.trace_id;
    record.header.fingerprint = "app-intent";
    record.payload = input.payload;
    fragment.records.push_back(record);
    return fragment;
  }
};

inline AppIntentRecord make_app_intent(const WalkerInputRecord& input) {
  AppIntentRecord intent;
  intent.intent_id = input.input_id + 2000;
  intent.source_kind = input.kind;
  intent.normalized_payload = input.payload;
  intent.trace_id = input.trace_id;
  return intent;
}

}  // namespace asking_star::v55
