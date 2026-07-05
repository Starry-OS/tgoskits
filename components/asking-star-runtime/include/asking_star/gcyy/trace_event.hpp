#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <cstdint>
#include <string>

namespace asking_star::gcyy {

struct TraceEvent {
  std::string event_id;
  std::string trace_id;
  std::string event_kind;
  std::string fragment_id;
  std::string gene_id;
  std::string charge_id;
  std::string cell_id;
  std::string projection_mode;
  std::string operator_name;
  std::string organ_id;
  std::string soil_request_id;
  GcyyStatus status{GcyyStatus::Ok};
  std::uint64_t latency_ns{0};
  std::string message;

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

