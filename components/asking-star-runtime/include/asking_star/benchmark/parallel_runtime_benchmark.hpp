#pragma once

#include <cstdint>
#include <string>

namespace asking_star::v5 {

struct BenchmarkRecord {
  std::uint64_t fragment_submit_latency_ns{0};
  std::uint64_t scheduler_step_latency_ns{0};
  std::uint64_t sun_step_latency_ns{0};
  std::uint64_t policy_projection_latency_ns{0};
  std::uint64_t timewheel_lookup_latency_ns{0};
  std::uint64_t ready_frontier_latency_ns{0};
  std::uint64_t algebra_ready_frontier_latency_ns{0};
  std::uint64_t organ_dispatch_latency_ns{0};
  std::uint64_t organ_queue_wait_ns{0};
  std::uint64_t soil_request_latency_ns{0};
  std::uint64_t soil_request_build_latency_ns{0};
  std::uint64_t soil_adapter_latency_ns{0};
  std::uint64_t return_rebuild_latency_ns{0};
  std::uint64_t trace_write_latency_ns{0};
  std::uint64_t end_to_end_latency_ns{0};
  double cache_hit_rate{0.0};
  std::uint32_t worker_count{1};
  std::string adapter_mode{"Mock"};
  std::string logical_result_hash;
};

}  // namespace asking_star::v5
