#pragma once

#include "asking_star/soil/soil_execution_status.hpp"

#include <cstdint>
#include <string>

namespace asking_star::soil::adapters {

struct StarryOSPlatformResult {
  SoilExecutionStatus status{SoilExecutionStatus::UnsupportedOperation};
  std::string payload;
  std::uint64_t bytes_transferred{0};
  std::string message;

  [[nodiscard]] bool ok() const;
};

class StarryOSPlatform {
 public:
  [[nodiscard]] StarryOSPlatformResult write_console(
      const std::string& bytes) const;
  [[nodiscard]] StarryOSPlatformResult write_uart(
      const std::string& bytes) const;
  [[nodiscard]] StarryOSPlatformResult write_log(
      const std::string& bytes) const;
  [[nodiscard]] StarryOSPlatformResult write_file(
      const std::string& path,
      const std::string& bytes) const;
  [[nodiscard]] StarryOSPlatformResult read_file(
      const std::string& path) const;
};

}  // namespace asking_star::soil::adapters
