#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/gcyy/charge_record.hpp"
#include "asking_star/gcyy/gene_record.hpp"
#include "asking_star/v55/walker_giant_ingress.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

using v5::ChargeRecord;
using v5::DigitalSetRefRecord;
using v5::GeneRecord;
using v5::RecordTypeTag;

struct AppGeneRecord {
  GeneRecord gene;
  std::string app_category;
};

struct AppChargeRecord {
  ChargeRecord charge;
  bool requires_sun_admission{true};
};

class AppGeneBuilder {
 public:
  [[nodiscard]] AppGeneRecord build(const AppIntentRecord& intent,
                                    std::uint64_t source_fragment_id) const {
    AppGeneRecord app_gene;
    app_gene.gene.gene_id = intent.intent_id + 1000;
    app_gene.gene.source_fragment_ref =
        make_app_ref(source_fragment_id, RecordTypeTag::Fragment, intent.trace_id);
    app_gene.gene.compressed_payload = intent.normalized_payload;
    app_gene.gene.trace_id = intent.trace_id;
    app_gene.app_category = category_for(intent.source_kind);
    return app_gene;
  }

 private:
  [[nodiscard]] static DigitalSetRefRecord make_app_ref(
      std::uint64_t id,
      RecordTypeTag tag,
      const std::string& trace_id) {
    DigitalSetRefRecord ref;
    ref.record_id = id;
    ref.expected_type_tag = tag;
    ref.expected_generation = 1;
    ref.trace_id = trace_id;
    return ref;
  }

  [[nodiscard]] static std::string category_for(WalkerInputKind kind) {
    switch (kind) {
      case WalkerInputKind::Command:
        return "command";
      case WalkerInputKind::NaturalLanguage:
        return "natural_language";
      case WalkerInputKind::UiEvent:
        return "ui_event";
      case WalkerInputKind::Sensor:
        return "sensor";
      case WalkerInputKind::AiResult:
        return "ai_result";
      case WalkerInputKind::Replay:
        return "replay";
      case WalkerInputKind::ExternalApp:
        return "external_app";
    }
    return "unknown";
  }
};

class AppChargeBuilder {
 public:
  [[nodiscard]] AppChargeRecord build(const AppGeneRecord& app_gene,
                                      std::uint64_t ttl_ticks) const {
    AppChargeRecord app_charge;
    app_charge.charge.charge_id = app_gene.gene.gene_id + 1000;
    app_charge.charge.gene_ref.record_id = app_gene.gene.gene_id;
    app_charge.charge.gene_ref.expected_type_tag = RecordTypeTag::Gene;
    app_charge.charge.gene_ref.expected_generation = 1;
    app_charge.charge.gene_ref.trace_id = app_gene.gene.trace_id;
    app_charge.charge.execution_intent = app_gene.gene.compressed_payload;
    app_charge.charge.ttl_ticks = ttl_ticks;
    app_charge.charge.trace_id = app_gene.gene.trace_id;
    app_charge.requires_sun_admission = true;
    return app_charge;
  }
};

}  // namespace asking_star::v55
