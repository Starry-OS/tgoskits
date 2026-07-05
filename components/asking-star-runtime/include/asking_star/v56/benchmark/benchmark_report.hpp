#pragma once

#include <string>
#include <vector>

namespace asking_star::v56::benchmark {

struct BenchRecord {
  std::string name;
  double avg{0.0};
  double p50{0.0};
  double p99{0.0};
  std::string unit;

  [[nodiscard]] bool is_valid() const;
};

struct TestRecord {
  std::string name;
  std::string result;

  [[nodiscard]] bool passed() const;
};

struct SentinelBenchmarkReport {
  std::vector<BenchRecord> benches;
  std::vector<TestRecord> tests;

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] bool all_tests_passed() const;
};

class SentinelBenchmarkParser {
 public:
  [[nodiscard]] SentinelBenchmarkReport parse(const std::string& text) const;
};

}  // namespace asking_star::v56::benchmark
