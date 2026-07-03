#pragma once

#include "core/charge/charge_gene_mapper.h"
#include "core/gene/gene_protocol.h"

#include <string>

namespace asking_star::core::charge {

enum class MonetaryForm {
  ChargeToken,
  GeneCodeCandidate,
  LedgerEntry,
};

struct LedgerEntryId {
  std::string value;

  [[nodiscard]] bool is_valid() const { return !value.empty(); }
};

struct LocalClearingRecord {
  std::string id;
  ChargeId source_charge_id;
  asking_star::core::gene::GeneId candidate_gene_id;
  MonetaryForm input_form{MonetaryForm::ChargeToken};
  MonetaryForm output_form{MonetaryForm::GeneCodeCandidate};

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && source_charge_id.is_valid() &&
           candidate_gene_id.is_valid();
  }

  [[nodiscard]] bool is_authoritative_fact() const { return false; }
};

struct CentralAdmissionRequest {
  std::string id;
  ChargeGeneCandidate candidate;
  asking_star::core::gene::GeneHandle handle;
  asking_star::core::gene::Influence influence;

  [[nodiscard]] bool is_valid() const {
    return !id.empty() && candidate.is_valid() && handle.is_valid() &&
           influence.is_valid();
  }
};

struct CentralAdmissionDecision {
  std::string id;
  asking_star::core::statechain::GenerationStatus status{
      asking_star::core::statechain::GenerationStatus::Pending};
  std::string reason;
  LedgerEntryId ledger_entry_id;
  bool may_append_genebank{false};

  [[nodiscard]] bool is_valid() const { return !id.empty() && !reason.empty(); }
};

class ChargeBanking {
 public:
  [[nodiscard]] LocalClearingRecord clear_locally(
      const ChargeGeneCandidate& candidate) const {
    return LocalClearingRecord{
        "local-clear-" + stable_protocol_digest(candidate.source_charge_id.value +
                                               ":" +
                                               candidate.code.gene_id.value),
        candidate.source_charge_id,
        candidate.code.gene_id};
  }

  [[nodiscard]] CentralAdmissionDecision request_admission(
      const CentralAdmissionRequest& request) const {
    auto generation = protocol_.evaluate(request.handle, request.influence);
    const bool accepted =
        generation.status ==
        asking_star::core::statechain::GenerationStatus::Generated;
    return CentralAdmissionDecision{
        "central-admission-" + stable_protocol_digest(request.id),
        generation.status,
        generation.reason,
        accepted ? make_ledger_entry_id(request, generation)
                 : LedgerEntryId{},
        accepted};
  }

  [[nodiscard]] bool writes_genebank_directly() const { return false; }

 private:
  [[nodiscard]] static LedgerEntryId make_ledger_entry_id(
      const CentralAdmissionRequest& request,
      const asking_star::core::gene::GenerationDecision& decision) {
    return LedgerEntryId{
        "ledger-" + stable_protocol_digest(request.candidate.code.gene_id.value +
                                           ":" + decision.reason)};
  }

  asking_star::core::gene::GeneProtocol protocol_;
};

}  // namespace asking_star::core::charge
