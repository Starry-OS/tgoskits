#include "asking_star/gcyy/mock_runtime_demo.hpp"

#include <cassert>
#include <string>

int main() {
  auto lines = asking_star::gcyy::run_mock_runtime_demo();
  assert(lines.size() == 9);
  assert(lines.front() == "[Walker] fragment created");
  assert(lines.back() == "[Trace] complete");
  bool saw_soil = false;
  for (const auto& line : lines) {
    if (line == "[Soil] kernel request mocked") {
      saw_soil = true;
    }
  }
  assert(saw_soil);
  return 0;
}
