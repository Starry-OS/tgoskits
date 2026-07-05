#include "asking_star/soil/adapters/starryos_platform.hpp"

#include <cstddef>

namespace asking_star::soil::adapters {
namespace {

#if defined(ASKING_STAR_TARGET_STARRYOS) && \
    defined(ASKING_STAR_ENABLE_STARRYOS_ADAPTER) && \
    ASKING_STAR_ENABLE_STARRYOS_ADAPTER && \
    defined(ASKING_STAR_STARRYOS_BOARD_REAL) && \
    ASKING_STAR_STARRYOS_BOARD_REAL
#define ASKING_STAR_STARRYOS_REAL_PLATFORM 1
#else
#define ASKING_STAR_STARRYOS_REAL_PLATFORM 0
#endif

#if ASKING_STAR_STARRYOS_REAL_PLATFORM && defined(__GNUC__)
extern "C" {
__attribute__((weak)) int asking_star_starryos_write_console(
    const char* data,
    std::size_t size);
__attribute__((weak)) int asking_star_starryos_write_uart(const char* data,
                                                         std::size_t size);
__attribute__((weak)) int asking_star_starryos_write_log(const char* data,
                                                        std::size_t size);
}
#endif

StarryOSPlatformResult unsupported(const std::string& message) {
  return {SoilExecutionStatus::UnsupportedOperation, "", 0, message};
}

StarryOSPlatformResult from_platform_status(int status,
                                            std::size_t bytes,
                                            const std::string& payload,
                                            const std::string& message) {
  if (status >= 0) {
    return {SoilExecutionStatus::Ok, payload, bytes, message};
  }
  return {SoilExecutionStatus::AdapterFailed,
          "",
          0,
          message + " failed in StarryOS platform hook"};
}

}  // namespace

bool StarryOSPlatformResult::ok() const {
  return status == SoilExecutionStatus::Ok;
}

StarryOSPlatformResult StarryOSPlatform::write_console(
    const std::string& bytes) const {
#if ASKING_STAR_STARRYOS_REAL_PLATFORM && defined(__GNUC__)
  if (asking_star_starryos_write_console != nullptr) {
    const int status =
        asking_star_starryos_write_console(bytes.data(), bytes.size());
    return from_platform_status(status, bytes.size(), bytes,
                                "StarryOS console write");
  }
#endif
  return unsupported("StarryOS console write unavailable in this build");
}

StarryOSPlatformResult StarryOSPlatform::write_uart(
    const std::string& bytes) const {
#if ASKING_STAR_STARRYOS_REAL_PLATFORM && defined(__GNUC__)
  if (asking_star_starryos_write_uart != nullptr) {
    const int status = asking_star_starryos_write_uart(bytes.data(), bytes.size());
    return from_platform_status(status, bytes.size(), bytes,
                                "StarryOS UART write");
  }
#endif
  return unsupported("StarryOS UART write unavailable in this build");
}

StarryOSPlatformResult StarryOSPlatform::write_log(
    const std::string& bytes) const {
#if ASKING_STAR_STARRYOS_REAL_PLATFORM && defined(__GNUC__)
  if (asking_star_starryos_write_log != nullptr) {
    const int status = asking_star_starryos_write_log(bytes.data(), bytes.size());
    return from_platform_status(status, bytes.size(), bytes,
                                "StarryOS log write");
  }
#endif
  return write_console(bytes);
}

StarryOSPlatformResult StarryOSPlatform::write_file(
    const std::string& path,
    const std::string& bytes) const {
  (void)path;
  (void)bytes;
  return unsupported("StarryOS file write is not implemented in Round 16");
}

StarryOSPlatformResult StarryOSPlatform::read_file(
    const std::string& path) const {
  (void)path;
  return unsupported("StarryOS file read is not implemented in Round 16");
}

}  // namespace asking_star::soil::adapters
