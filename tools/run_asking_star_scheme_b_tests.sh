#!/usr/bin/env bash
set -uo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo="${1:-$(cd "$script_dir/.." && pwd)}"
cd "$repo"
mkdir -p ci-logs

stamp="$(date +%Y%m%d_%H%M%S)"
log="ci-logs/asking-star-scheme-b-${stamp}.log"

{
  echo "LOG=$log"
  date
  echo "REPO=$repo"
  echo "STEP=cmake_configure"
  cmake -S components/asking-star-soil -B build/asking-star-scheme-b
  config_code=$?
  echo "CONFIG_EXIT_CODE:$config_code"
  if [[ "$config_code" -ne 0 ]]; then
    date
    echo "EXIT_CODE:$config_code"
    exit "$config_code"
  fi

  echo "STEP=cmake_build"
  cmake --build build/asking-star-scheme-b
  build_code=$?
  echo "BUILD_EXIT_CODE:$build_code"
  if [[ "$build_code" -ne 0 ]]; then
    date
    echo "EXIT_CODE:$build_code"
    exit "$build_code"
  fi

  echo "STEP=ctest"
  ctest --test-dir build/asking-star-scheme-b --output-on-failure
  test_code=$?
  echo "CTEST_EXIT_CODE:$test_code"
  date
  echo "EXIT_CODE:$test_code"
  exit "$test_code"
} 2>&1 | tee "$log"

exit "${PIPESTATUS[0]}"
