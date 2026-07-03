#pragma once

#include "asking_star/gcyy/charge_view.hpp"
#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gene_view.hpp"
#include "asking_star/gcyy/organ_runtime.hpp"
#include "asking_star/gcyy/soil_runtime.hpp"
#include "asking_star/gcyy/sun_orchestrator.hpp"
#include "core/charge/charge_token.h"
#include "core/gene/gene_code.h"

#include <string>
#include <vector>

namespace asking_star::legacy {

struct LegacySchedulerSnapshot {
  std::string scheduler_id;
  std::string trace_id;
};

struct LegacyKernelSoilSnapshot {
  std::string soil_id;
  std::string trace_id;
};

struct LegacyWorkerNode {
  std::string worker_id;
  std::string trace_id;
};

struct LegacyTaskGraph {
  std::string graph_id;
  std::string trace_id;
  std::vector<std::string> task_labels;
};

// Maps V2/V3 legacy concepts into V5 protocol surfaces without executing them.
class LegacyAdapter {
 public:
  [[nodiscard]] asking_star::gcyy::GeneView map_gene_code(
      const asking_star::core::gene::GeneCode& code,
      std::string trace_id) const;
  [[nodiscard]] asking_star::gcyy::ChargeView map_charge_token(
      const asking_star::core::charge::ChargeToken& token,
      std::string trace_id) const;
  [[nodiscard]] asking_star::gcyy::SunOrchestrator map_scheduler(
      const LegacySchedulerSnapshot& scheduler) const;
  [[nodiscard]] asking_star::gcyy::SoilRuntime map_kernel_soil(
      const LegacyKernelSoilSnapshot& soil) const;
  [[nodiscard]] asking_star::gcyy::OrganResult map_worker_node(
      const LegacyWorkerNode& worker) const;
  [[nodiscard]] asking_star::gcyy::DigitalSetFragment map_task_graph(
      const LegacyTaskGraph& graph) const;
};

}  // namespace asking_star::legacy

