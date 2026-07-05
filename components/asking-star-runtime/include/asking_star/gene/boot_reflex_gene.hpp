#pragma once

#include "asking_star/gcyy/gene_view.hpp"
#include "asking_star/gcyy/runtime_budget.hpp"
#include "asking_star/soil/soil_execution_status.hpp"

#include <string>

namespace asking_star::gene {

enum class ReflexTrigger {
  Boot,
  FirstCommand,
  Failure,
};

enum class ReflexPhase {
  BootBegin,
  Warmup,
  BoundaryCheck,
  Trace,
  Fallback,
  Return,
};

struct BootReflexGene {
  std::string gene_id;
  std::string name;
  ReflexTrigger trigger{ReflexTrigger::Boot};
  ReflexPhase phase{ReflexPhase::BootBegin};
  std::string star_tag;
  std::string gene_hash;
  asking_star::soil::OperationKind preferred_operation{
      asking_star::soil::OperationKind::Noop};
  std::string target_kind{"boot.reflex"};
  int priority{0};
  asking_star::gcyy::RuntimeBudget budget;
  bool immutable{true};
  bool enabled{true};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] asking_star::gcyy::GeneView to_gene_view(
      const std::string& trace_id) const;
  [[nodiscard]] std::string debug_dump() const;
};

[[nodiscard]] const char* to_string(ReflexTrigger trigger);
[[nodiscard]] const char* to_string(ReflexPhase phase);

}  // namespace asking_star::gene
