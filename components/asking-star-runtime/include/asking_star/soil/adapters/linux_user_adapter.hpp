#pragma once

#include "asking_star/soil/adapters/kernel_adapter.hpp"

#include <filesystem>

namespace asking_star::soil::adapters {

class LinuxUserAdapter final : public KernelAdapter {
 public:
  explicit LinuxUserAdapter(std::filesystem::path runtime_tmp_dir =
                                std::filesystem::path{"runtime_tmp"});

  [[nodiscard]] KernelResult execute(const KernelRequest& request) const override;
  [[nodiscard]] const std::filesystem::path& runtime_tmp_dir() const;
  [[nodiscard]] bool is_safe_relative_path(const std::string& path) const;

 private:
  [[nodiscard]] std::filesystem::path resolve_safe_path(
      const std::string& path) const;

  std::filesystem::path runtime_tmp_dir_;
};

}  // namespace asking_star::soil::adapters

