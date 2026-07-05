#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
default_dst="$(cd "$script_dir/.." && pwd)"

src="${1:-/mnt/d/proj/starryos-merged/AskingStar}"
dst="${2:-$default_dst}"

if [[ ! -d "$src/include/asking_star" || ! -d "$src/src/gcyy" || ! -d "$src/src/soil" ]]; then
    echo "invalid AskingStar source: $src" >&2
    exit 2
fi

cd "$dst"

mkdir -p \
    components/asking-star-runtime/src \
    components/asking-star-runtime/tests/unit \
    components/asking-star-runtime/tests/integration \
    components/asking-star-soil/src \
    components/asking-star-soil/include/asking_star \
    components/asking-star-soil/tests/unit \
    components/asking-star-soil/tests/integration \
    components/asking-star-soil/core

cp -a "$src/include" components/asking-star-runtime/
cp -a \
    "$src/src/digitalset" \
    "$src/src/timeline" \
    "$src/src/scheduler" \
    "$src/src/organ" \
    "$src/src/gcyy" \
    components/asking-star-runtime/src/
mkdir -p components/asking-star-runtime/src/v55
cp -a "$src/src/v55/rknn_boardreal_test_record.cpp" components/asking-star-runtime/src/v55/

cp -a \
    "$src/tests/unit/gcyy" \
    "$src/tests/unit/digitalset" \
    "$src/tests/unit/v55" \
    components/asking-star-runtime/tests/unit/
cp -a "$src/tests/v55" components/asking-star-runtime/tests/
cp -a \
    "$src/tests/integration/test_fragment_to_cell_record.cpp" \
    "$src/tests/integration/test_cellref_to_soil_kernel_request_mainline.cpp" \
    "$src/tests/integration/test_v55_app_charge_sun_admission.cpp" \
    "$src/tests/integration/test_v55_pouch_parallel_trace.cpp" \
    "$src/tests/integration/test_v55_replay_ai_chamber.cpp" \
    "$src/tests/integration/test_v55_rknn_runtime_chamber.cpp" \
    components/asking-star-runtime/tests/integration/

cp -a "$src/include/asking_star/soil" components/asking-star-soil/include/asking_star/
cp -a "$src/src/soil" components/asking-star-soil/src/
cp -a \
    "$src/core/kernelsoil" \
    "$src/core/boot" \
    "$src/core/charge" \
    "$src/core/dualchain" \
    "$src/core/event" \
    "$src/core/gene" \
    "$src/core/genebank" \
    "$src/core/responsibility" \
    "$src/core/statechain" \
    components/asking-star-soil/core/
cp -a "$src/tests/unit/soil" components/asking-star-soil/tests/unit/
cp -a \
    "$src/tests/integration/test_soil_contract_mock.cpp" \
    "$src/tests/integration/test_soil_forward_organ_return_rebuilder.cpp" \
    "$src/tests/integration/test_soil_linux_user_flow.cpp" \
    "$src/tests/integration/test_soil_starryos_dryrun_flow.cpp" \
    "$src/tests/integration/test_v55_chamber_starryos_dryrun.cpp" \
    "$src/tests/integration/test_v55_stable_starry_dryrun.cpp" \
    "$src/tests/integration/test_v55_qemu_report_bridge.cpp" \
    components/asking-star-soil/tests/integration/
cp -a "$src/tests/test_qemu_dry_run_integration.cpp" components/asking-star-soil/tests/

find components/asking-star-runtime components/asking-star-soil -type f | sort
