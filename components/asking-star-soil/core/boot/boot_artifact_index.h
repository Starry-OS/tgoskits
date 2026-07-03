#pragma once

#include <optional>
#include <string>
#include <unordered_map>

namespace asking_star::core::boot {

struct StarryOSArtifact {
  std::string artifact_id;
  std::string kernel_image;
  std::string rootfs_image;
  std::string boot_strategy{"qemu-aarch64-virt"};
  std::string serial_endpoint{"127.0.0.1:19090"};

  [[nodiscard]] bool is_valid() const {
    return !artifact_id.empty() && !kernel_image.empty() &&
           !rootfs_image.empty() && !boot_strategy.empty() &&
           !serial_endpoint.empty();
  }
};

class JianmuArtifactIndex {
 public:
  void index_artifact(StarryOSArtifact artifact) {
    if (!artifact.is_valid()) {
      return;
    }
    artifacts_by_id_[artifact.artifact_id] = artifact;
    if (default_artifact_id_.empty()) {
      default_artifact_id_ = artifact.artifact_id;
    }
  }

  [[nodiscard]] std::optional<StarryOSArtifact> select(
      const std::string& artifact_id) const {
    if (!artifact_id.empty()) {
      auto it = artifacts_by_id_.find(artifact_id);
      if (it != artifacts_by_id_.end()) {
        return it->second;
      }
      return std::nullopt;
    }
    if (default_artifact_id_.empty()) {
      return std::nullopt;
    }
    auto it = artifacts_by_id_.find(default_artifact_id_);
    if (it == artifacts_by_id_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  [[nodiscard]] bool controls_qemu_directly() const { return false; }

 private:
  std::unordered_map<std::string, StarryOSArtifact> artifacts_by_id_;
  std::string default_artifact_id_;
};

}  // namespace asking_star::core::boot
