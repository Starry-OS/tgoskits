---
sidebar_position: 1
---

# Asking Star Scheme-B Overview

This document explains where the Asking Star Scheme-B functionality lives in
TGOSKits and what the current integration proves.

Scheme-B imports Asking Star as reviewable components instead of wiring it
directly into ArceOS, AxVisor, or StarryOS internals:

- `components/asking-star-runtime`
- `components/asking-star-soil`
- `tools/import_asking_star_scheme_b.sh`
- `tools/run_asking_star_scheme_b_tests.sh`

The import is a componentization step. It provides a buildable and testable
runtime/adapter foundation for later StarryOS integration, but it does not claim
complete RKNN/NPU, camera, motor, robot closed-loop, or official self-hosted
board CI completion.

## Why Walker Is Inside The Runtime Commit

The existing Git commit is named `components(asking-star): add runtime
component`, but it includes more than the low-level `StarRuntime` facade.

Walker-Giant and the related V5.5 demo surfaces are part of the runtime
component because they are semantic runtime entry and projection surfaces, not a
separate OS or board layer.

The Walker-related code is under:

- `components/asking-star-runtime/include/asking_star/walker/`
- `components/asking-star-runtime/include/asking_star/v55/`
- `components/asking-star-runtime/tests/v55/`
- `components/asking-star-runtime/tests/integration/`

Important files include:

- `walker/walker_runtime.hpp`
- `walker/walker_input.hpp`
- `v55/walker_giant_ingress.hpp`
- `v55/skin_ui_projection.hpp`
- `v55/algebra_skeleton.hpp`
- `v55/chamber_runtime.hpp`
- `v55/chamber_pouch.hpp`
- `v55/reflex_gene_bank.hpp`
- `v55/v55_demo_pipeline.hpp`

So the functional boundary is:

```text
Walker / Skin / App input
  -> DigitalSetFragment
  -> StarRuntime
  -> Gene / Charge / DigitalCell
  -> Sun admission
  -> OrganRuntime
  -> SoilRuntime
  -> KernelAdapter
  -> KernelResult
  -> ReturnRebuilder
  -> Trace
```

## Five-Layer Mapping

The Asking Star design uses a layered semantic runtime model. In this Scheme-B
import, those layers map to TGOSKits components as follows.

| Design layer | Current Scheme-B location | Responsibility |
| --- | --- | --- |
| Outer application / Walker surface | `asking-star-runtime/include/asking_star/walker`, `asking-star-runtime/include/asking_star/v55/skin_ui_projection.hpp` | Normalize commands, UI events, app intents, replay inputs, and AI results into runtime-visible records. |
| Primordial / DigitalSet fact layer | `asking-star-runtime/include/asking_star/digitalset`, `asking-star-runtime/include/asking_star/timeline` | Store facts as records and references. Keep `Record`, `View`, and `RefRecord` separate. |
| StarRuntime / semantic interpretation | `asking-star-runtime/include/asking_star/gcyy`, `asking-star-runtime/include/asking_star/runtime` | Interpret `DigitalSetFragment` into `Gene`, `Charge`, and `DigitalCell` runtime views. |
| Sun / Organ execution layer | `asking-star-runtime/include/asking_star/gcyy/sun_orchestrator.hpp`, `asking-star-runtime/include/asking_star/organ` | Admit work by budget/policy and execute admitted semantic work units. |
| Soil / OS adapter boundary | `components/asking-star-soil`, `asking-star-runtime/include/asking_star/soil` | Convert runtime work into kernel requests/results. Keep OS/ABI/syscall/driver translation out of `StarRuntime`. |

## What Asking Star Solves Here

This PR turns the Asking Star initial-round design into code that upstream
maintainers can inspect and test.

It specifically addresses these engineering gaps:

1. `DigitalSet` becomes a concrete fact carrier rather than only a design term.
   Records, refs, stores, fragments, and resolver behavior are present in code.

2. `Gene`, `Charge`, and `DigitalCell` become explicit runtime forms. They are
   not ordinary object pointers and they do not replace the underlying
   `DigitalSet` record model.

3. Walker-Giant, Skin projection, Chamber, Pouch, ReflexGene, and demo pipeline
   surfaces are represented as runtime-level structures. They describe how
   inputs and observations enter the semantic runtime without directly touching
   the OS boundary.

4. `SoilRuntime` is the only OS/ABI boundary. `StarRuntime`, `OrganRuntime`, and
   Walker surfaces do not call StarryOS directly.

5. Mock, Linux-user, StarryOS dry-run, QEMU dry-run, and BoardReal evidence are
   kept separate. Guard tests prevent dry-run or host evidence from being
   reported as board evidence.

## Current Evidence

The current Scheme-B component evidence is:

- Scheme-B component smoke: 31/31 tests passed.
- TGOSKits root `fmt`, `clippy`, `sync-lint`, and `test` passed locally.
- Official-container local QEMU matrix passed: 11/11.

The QEMU matrix covers:

- ArceOS: `x86_64`, `aarch64`, `riscv64`, `loongarch64`
- Starry: `x86_64`, `aarch64`, `riscv64`, `loongarch64`
- AxVisor: `aarch64`, `riscv64`, `loongarch64`

## Not Claimed

This Scheme-B import does not claim:

- official self-hosted CI pass;
- RK3588 / BoardReal pass without separate board logs;
- complete StarryOS-native RKNN/NPU execution;
- camera input;
- UART motor control;
- full robot closed-loop behavior;
- performance superiority over a Linux baseline.

Those require separate board evidence, serial logs, runner logs, image hashes,
and task-specific validation.

## Suggested Review Order

1. Review this document to understand the functional boundary.
2. Review `tools/import_asking_star_scheme_b.sh` and
   `tools/run_asking_star_scheme_b_tests.sh`.
3. Review `components/asking-star-runtime` for `DigitalSet`, Walker, V5.5,
   GCYY, Sun, Organ, and trace structures.
4. Review `components/asking-star-soil` for request/result, adapter, return
   rebuild, QEMU dry-run, and BoardReal guard behavior.
5. Review CI/QEMU fixes separately from the Asking Star component import.
