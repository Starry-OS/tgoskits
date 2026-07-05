#pragma once

#include <string>
#include <vector>

namespace asking_star::gcyy {

// Runs the complete mock GCYY loop for Round 10 validation.
[[nodiscard]] std::vector<std::string> run_mock_runtime_demo();

// Runs the Round 12 full mock loop beginning at WalkerRuntime.
[[nodiscard]] std::vector<std::string> run_full_mock_runtime_demo();

}  // namespace asking_star::gcyy
