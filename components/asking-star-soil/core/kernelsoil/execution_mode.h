#pragma once

namespace asking_star::core::kernelsoil {

enum class ExecutionMode {
  Mock,
  Qemu,
  Real,
};

inline const char* to_string(ExecutionMode mode) {
  switch (mode) {
    case ExecutionMode::Mock:
      return "MOCK";
    case ExecutionMode::Qemu:
      return "QEMU";
    case ExecutionMode::Real:
      return "REAL";
  }
  return "MOCK";
}

}  // namespace asking_star::core::kernelsoil
