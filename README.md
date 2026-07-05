<h1 align="center">TGOSKits</h1>

<p align="center">An integrated repository for operating system and virtualization development</p>

<div align="center">

[![Build & Test](https://github.com/rcore-os/tgoskits/actions/workflows/ci.yml/badge.svg)](https://github.com/rcore-os/tgoskits/actions/workflows/ci.yml)
[![Rust](https://img.shields.io/badge/edition-2024-orange.svg)](https://www.rust-lang.org/)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](./LICENSE)

</div>

English | [中文](README_CN.md)

## Asking Star Scheme-B Runtime Components

### Project Background

This fork carries an Asking Star Scheme-B componentization branch maintained by
the Yi Astra team from Tianjin University. The team's work focuses on StarryOS,
RK3588 edge-intelligence platforms, AI inference adaptation, and embodied
intelligence application migration.

During this work, we organized Asking Star as a semantic runtime design around
StarryOS boot-chain validation, AI inference backend adaptation, runtime state
recording, and test evidence management. Asking Star is not intended to replace
the StarryOS kernel, nor to reimplement a full operating system. It adds a
semantic runtime layer above the OS boundary to organize application intent, AI
inference requests, system-boundary calls, runtime state, and validation
evidence.

Following the suggestion to share this design and implementation direction with
the TGOSKits / StarryOS / ArceOS / AxVisor upstream communities, this branch
keeps the integration small, componentized, and reviewable. It is an
exploratory runtime component set and adapter-boundary proposal, submitted for
open discussion and incremental review rather than as a replacement for the
existing upstream architecture.

### Repository Positioning

This branch adds Asking Star Scheme-B as self-contained runtime and Soil
adapter components:

```text
components/asking-star-runtime
components/asking-star-soil
tools/import_asking_star_scheme_b.sh
tools/run_asking_star_scheme_b_tests.sh
docs/docs/asking-star/scheme-b-overview.md
```

`asking-star-runtime` contains the semantic runtime side: `DigitalSet`, `Gene /
Charge`, `DigitalCell`, `StarRuntime`, `Sun / Organ`, Walker-Giant ingress,
Primordial seed refs, AlgebraSkeleton, TimelineJoint, Star-layer vessel
transport, MultiChamber runtime, ChamberPouch observation, SkinUI projection,
ReflexGeneBank, and trace records.

`asking-star-soil` contains the OS/ABI adapter boundary: `KernelRequest`,
`KernelResult`, `ReturnRebuilder`, Mock / LinuxUser / StarryOS adapter surfaces,
QEMU dry-run records, and BoardReal guard records.

The tools provide reproducible import and smoke-test entry points for a TGOSKits
checkout.

### Implemented Architecture Surface

This branch does not only contain a minimal `StarRuntime` facade. It carries the
core Asking Star V5/V5.5/V5.6 implementation surface that was prepared in the
Asking Star workspace and then componentized for TGOSKits review.

Important implemented areas include:

- Walker-Giant ingress:
  `components/asking-star-runtime/include/asking_star/v55/walker_giant_ingress.hpp`
- Primordial startup seed refs:
  `components/asking-star-runtime/include/asking_star/v55/primordial_seed_refs.hpp`
- Main time-axis skeleton and timeline joints:
  `components/asking-star-runtime/include/asking_star/v55/algebra_skeleton.hpp`
- Star-layer vessel transport:
  `components/asking-star-runtime/include/asking_star/v56/vessel/`
- Application gene/charge builders:
  `components/asking-star-runtime/include/asking_star/v55/app_gene_charge.hpp`
- MultiChamber placement and execution records:
  `components/asking-star-runtime/include/asking_star/v55/chamber_runtime.hpp`
- ChamberPouch observation, health, fallback, and reflex-candidate surface:
  `components/asking-star-runtime/include/asking_star/v55/chamber_pouch.hpp`
- Replay, RKNN, and StarryOS dry-run chamber surfaces:
  `components/asking-star-runtime/include/asking_star/v55/replay_ai_chamber.hpp`,
  `components/asking-star-runtime/include/asking_star/v55/rknn_runtime_chamber.hpp`,
  and `components/asking-star-runtime/include/asking_star/v55/chamber_starryos_dryrun_bridge.hpp`
- Soil MultiChamber adapter:
  `components/asking-star-runtime/include/asking_star/v55/soil_multichamber_adapter.hpp`
- Skin/UI state projection:
  `components/asking-star-runtime/include/asking_star/v55/skin_ui_projection.hpp`
- Reflex gene and preset-charge path:
  `components/asking-star-runtime/include/asking_star/v55/reflex_gene_bank.hpp`
- V5.5 demo pipeline:
  `components/asking-star-runtime/include/asking_star/v55/v55_demo_pipeline.hpp`

The matching tests are under
`components/asking-star-runtime/tests/v55/`,
`components/asking-star-runtime/tests/unit/v55/`, and
`components/asking-star-runtime/tests/integration/`. They cover the
Primordial seed refs, AlgebraSkeleton / TimelineJoint mounting,
Walker-to-app-intent conversion, app Gene / Charge generation,
Chamber / Pouch / Reflex / Soil flow, Skin projection, and demo-pipeline
surfaces.

### Architecture Overview

Asking Star uses a layered structure from application intent to runtime
interpretation and OS-boundary adaptation. Application input can come from a
shell, tool, AI demo, external service, replay stream, or future robot task
entry. Runtime state is recorded through `DigitalSet` records. The Soil layer
then lowers semantic requests into OS/ABI requests. Backends can be Mock,
Replay, Linux user, QEMU dry-run, StarryOS adapter, or a separately evidenced
BoardReal path.

The intended flow is:

```text
App / Intent
  -> DigitalSetRecord / DigitalSetFragment
  -> WalkerIngress / SkinUIProjection
  -> PrimordialDigitalSet seed refs
  -> StarRuntime / Gene / Charge / DigitalCell
  -> AlgebraSkeleton / TimelineJoint
  -> Star-layer VesselBus transport
  -> Sun admission
  -> OrganRuntime / MultiChamber placement
  -> ChamberRuntime / ChamberPouchView
  -> SoilRuntime
  -> KernelAdapter
  -> KernelResult
  -> ReturnRebuilder
  -> TraceEventRecord
```

Asking Star Runtime does not replace StarryOS kernel scheduling. It adds a task
organization, capability selection, chamber selection, state-feedback, and
evidence-recording layer above the OS. The current Scheme-B implementation uses
`DigitalSet` as the fact carrier, Primordial seed refs as the startup
interpretation root, `Gene / Charge` as semantic representations, `DigitalCell`
as the minimum runtime unit, `AlgebraSkeleton` as the main time-axis skeleton,
`TimelineJoint` and Star-layer vessels as the record transport path, `Sun /
Organ` as admission and execution organization, MultiChamber / ChamberPouch as
execution-environment and observation surfaces, `SoilRuntime` as the OS/ABI
boundary, and trace records as the return path for validation and replay.

### Problems Addressed

Edge-intelligence systems often couple application logic, AI inference, OS
services, drivers, device nodes, syscalls, ioctls, and hardware behavior. This
works in a mature Linux environment, but it becomes difficult to migrate or
compare behavior across StarryOS, QEMU, Mock, Replay, Linux user, and real board
validation.

Asking Star is intended to make these boundaries explicit:

1. Reduce coupling between application intent and OS/ABI details.
2. Keep AI inference results, `KernelRequest`, `KernelResult`, trace, and logs
   in a unified record path.
3. Separate Mock, Replay, Linux baseline, QEMU dry-run, StarryOS adapter, and
   BoardReal evidence.
4. Keep upper-level task organization separate from lower-level driver calls.
5. Provide a fact carrier that supports replay, audit, and comparison.
6. Keep local validation and real board validation visibly separate.

### Core Design Notes

`DigitalSet` is the unified fact carrier. Application intent, task dependencies,
AI inference results, kernel requests, kernel results, trace events, and Soil
return values should enter the runtime as records before being interpreted by
`StarRuntime`.

`StarRuntime` is the semantic interpretation center. It does not directly call
syscalls, ioctls, mmap, device drivers, or StarryOS internals. It answers what a
task means and how it should become a runtime unit.

`Gene`, `Charge`, and `DigitalCell` are semantic runtime forms. `Gene` models a
compressed or indexed experience. `Charge` models an executable runtime intent.
`DigitalCell` combines them into the minimum semantic runtime unit.

`PrimordialDigitalSet` is the startup interpretation root. It carries seed refs
and startup interpretation metadata without absorbing the full timeline,
chamber state, pouch state, trace store, scheduling policy, or reflex bank.

`AlgebraSkeleton` is the main time-axis skeleton. `TimelineJoint` mounts
references for Walker input, app intent, app Gene, app Charge, DigitalCell,
chamber placement, selected chamber, ChamberPouch, Organ dispatch, Soil
request, kernel result, trace event, and reflex candidate.

The Star-layer vessel path is implemented under `asking_star/v56/vessel`. It
models transport, gates, routes, packets, policy, taps, recovery, and blocking
records for runtime information moving across the Star layer. In design terms,
this is the "blood vessel" surface: it carries facts and results without
collapsing them into raw pointers or direct OS calls.

`Sun` and `Organ` separate admission from execution organization. `Sun` handles
logical rhythm, budget, permission, and admission decisions. `OrganRuntime`
organizes admitted `DigitalCell` execution without bypassing Soil.

`ChamberRuntime` and `ChamberPlacementPolicy` select execution environments,
including Mock, Replay, StableStarry, Linux external service, RKNN runtime, and
dry-run adapter surfaces. `ChamberPouchView` is the care and observation layer:
it records health, output, fallback, trace-facing data, adapter mode, and
reflex candidates, but it does not bypass Soil or execute OS calls directly.

`SkinUIProjection` is the readable/input-facing projection layer. It can project
runtime state and convert UI events into Walker input records, but it does not
switch chambers, call Soil, or write board evidence by itself.

`SoilRuntime` is the only OS/ABI boundary. It translates semantic work into
`KernelRequest`, `AbiPacket`, or adapter requests, then rebuilds low-level
results into `KernelResult` and `DigitalSetFragment`.

### Evidence Boundary

Asking Star keeps validation modes separate:

- Mock: local logic validation.
- Replay: historical result replay.
- Linux user: Linux userspace adapter rehearsal.
- QEMU dry-run: virtual hardware or boot-path prescreening.
- StarryOS adapter: StarryOS-facing adapter boundary.
- BoardReal: real board logs or runner-provided evidence only.

This branch does not treat Mock, Replay, Linux baseline, or QEMU dry-run output
as BoardReal evidence.

### Current Validation Scope

The current branch validates:

- Asking Star runtime components build independently.
- The `DigitalSet / Gene / Charge / DigitalCell` path is testable.
- Walker-Giant ingress, Primordial seed refs, AlgebraSkeleton,
  TimelineJoint, Star-layer vessel, MultiChamber, ChamberPouch, Skin projection,
  and ReflexGene surfaces are present in component code.
- The runtime-to-Soil adapter path is testable.
- Mock, LinuxUser, QEMU dry-run, and BoardReal guard paths are distinguishable.
- Soil remains the only OS/ABI boundary.

The current branch does not claim:

- complete StarryOS-native RKNN / NPU execution;
- complete camera input integration;
- complete motor or robotic-arm control;
- complete robot task closed-loop behavior;
- local validation replacing upstream CI or self-hosted runner evidence.

### Relationship With Upstream

TGOSKits, StarryOS, ArceOS, and AxVisor each have clear engineering boundaries
and maintenance rhythms. This branch does not ask upstream maintainers to accept
the full Asking Star architecture at once.

The goal is to share a componentized implementation so maintainers can review:

- whether the `DigitalSet / Record / View / RefRecord` boundary is clear;
- whether the Walker / Primordial / Skeleton / Vessel / Chamber / Pouch
  boundaries are understandable and reviewable;
- whether the runtime component can build and test independently;
- whether the Soil adapter contract is a useful OS/ABI boundary;
- whether Mock / dry-run / BoardReal evidence separation is valuable;
- whether future pieces should be split into smaller upstreamable patches.

### Collaboration Note

Asking Star is an exploratory semantic-runtime direction from the Yi Astra
team's StarryOS/RK3588 engineering work. We appreciate the upstream work around
TGOSKits, StarryOS, ArceOS, and AxVisor.

We hope to collaborate in an open and respectful way. If maintainers prefer
different directory placement, API naming, component boundaries, test layout, or
documentation scope, we are willing to adjust the branch according to community
feedback.


TGOSKits is an integrated repository for operating system and virtualization development. It uses Git Subtree to manage more than 60 standalone component repositories, bringing ArceOS, StarryOS, Axvisor, and related platform crates into a single workspace for component-level development, cross-system integration, and unified testing.

## 1. Quick Navigation

This repository contains multiple systems and dozens of standalone components. Different development goals map to different documents and command entry points. The table below helps you quickly find the most relevant document and the shortest useful command for your current task.

| Your Goal | Recommended First Reading | Shortest Command |
| --- | --- | --- |
| First successful run | [docs/docs/quickstart/overview.md](docs/docs/quickstart/overview.md) | `cargo xtask arceos qemu --package ax-helloworld --arch aarch64` |
| ArceOS quick start | [docs/docs/quickstart/arceos.md](docs/docs/quickstart/arceos.md) | `cargo xtask arceos qemu --package ax-helloworld --arch aarch64` |
| StarryOS quick start | [docs/docs/quickstart/starryos.md](docs/docs/quickstart/starryos.md) | `cargo xtask starry qemu --arch aarch64` |
| Axvisor quick start | [docs/docs/quickstart/axvisor.md](docs/docs/quickstart/axvisor.md) | `cargo xtask axvisor qemu --arch aarch64` |
| Full development example | [docs/docs/design/reference/demo.md](docs/docs/design/reference/demo.md) | A complete example for creating or modifying a component from scratch |
| Component development guide | [docs/docs/design/reference/components.md](docs/docs/design/reference/components.md) | Start from `components/` or `os/arceos/modules/` |
| Develop ArceOS | [docs/docs/design/systems/arceos-guide.md](docs/docs/design/systems/arceos-guide.md) | `cargo xtask arceos qemu --package ax-helloworld --arch aarch64` |
| Develop StarryOS | [docs/docs/design/systems/starryos-guide.md](docs/docs/design/systems/starryos-guide.md) | `cargo xtask starry qemu --arch aarch64` |
| Develop Axvisor | [docs/docs/design/systems/axvisor-guide.md](docs/docs/design/systems/axvisor-guide.md) | `cargo xtask axvisor qemu --arch aarch64` |
| Understand the build and test matrix | [docs/docs/design/build/flow.md](docs/docs/design/build/flow.md) | `cargo xtask test` |
| Understand how the repository organizes many standalone components | [docs/docs/design/reference/repo.md](docs/docs/design/reference/repo.md) | `python3 scripts/repo/repo.py list` |

## 2. Repository Layout

The repository is organized by responsibility: `components/` stores reusable standalone components, `os/` stores the source code of the three target systems, `platform/` stores platform-related crates, and `docs/` centralizes developer documentation. `scripts/repo/` provides subtree management tools.

```text
tgoskits/
├── components/                # standalone component crates managed by subtree
├── os/
│   ├── arceos/                # ArceOS: modules / api / ulib / examples
│   ├── StarryOS/              # StarryOS: kernel / starryos / make
│   └── axvisor/               # Axvisor: src / configs / local xtask
├── platform/                  # platform-related crates
├── test-suit/                 # ArceOS / StarryOS system tests
├── xtask/                     # root tg-xtask
├── scripts/
│   └── repo/                  # subtree management scripts and repos.csv
└── docs/                      # developer documentation
```

The repository follows a three-layer branch strategy: `main`, `dev`, and feature branches. `main` serves as the stable baseline, `dev` serves as the integration branch for development and CI validation, and developers create feature branches from `dev` and merge back via PRs. Direct pushes to `main` are forbidden.

| Branch | Responsibility | Rule |
| --- | --- | --- |
| `main` | Stable release branch, regularly merged from `dev` | No direct push |
| `dev` | Integration branch for development and CI | Merge through PR |
| Feature branches | Individual development branches | Submit PRs to `dev` when ready |

```text
feature/* ──PR──► dev
                   │
                regular merge
                   ▼
                 main
```

If you need to synchronize with component repositories, maintainers should explicitly run `scripts/repo/repo.py pull/push`. See [docs/docs/design/reference/repo.md](docs/docs/design/reference/repo.md) for details.

## 3. Quick Experience

The following commands provide the shortest runnable path for the three systems, helping you verify that your environment is ready. All three systems use the unified `cargo xtask <os> <subcommand>` entry point; `cargo arceos`, `cargo starry`, and `cargo axvisor` are only equivalent aliases. ArceOS can run directly, StarryOS requires a prepared rootfs, and Axvisor requires guest images and configuration prepared beforehand.

```bash
git clone https://github.com/rcore-os/tgoskits.git
cd tgoskits

# ArceOS: fastest Hello World path
cargo xtask arceos qemu --package ax-helloworld --arch aarch64
# Equivalent alias
cargo arceos qemu --package ax-helloworld --arch aarch64

# StarryOS: prepare rootfs before the first run
cargo xtask starry qemu --arch aarch64
# Equivalent alias
cargo starry qemu --arch aarch64

# Axvisor: recommended to use the official setup script for guest and rootfs
cargo xtask axvisor qemu --arch aarch64
# Equivalent alias
cargo axvisor qemu --arch aarch64
```

Axvisor cannot be started only with `build/qemu`, because guest images, VM configuration, and rootfs are still required before runtime. It is recommended to use `os/axvisor/scripts/setup_qemu.sh` to prepare those runtime resources first, then run `cargo xtask axvisor qemu --arch <arch>`. See [docs/docs/manual/deploy/qemu.md](docs/docs/manual/deploy/qemu.md) and [docs/docs/design/systems/axvisor-guide.md](docs/docs/design/systems/axvisor-guide.md) for the full workflow.

## 4. Quick Development

The repository includes built-in `.vscode/launch.json` and `.vscode/tasks.json`. After opening the workspace in VS Code, press `F5` to start debugging in one click — it automatically performs a debug build, launches QEMU (with GDB stub), attaches LLDB, and hits a breakpoint. Each system provides **Main** (stops at the main application entry) and **Boot** (sets multiple breakpoints at platform boot / runtime initialization) entry types, covering different debugging needs from early boot to business logic.

![VS Code debug target selection](docs/docs/design/debug/images/debug_target.png)

Before first use, ensure the [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) extension is installed, `rustup target add aarch64-unknown-none-softfloat` has been executed, and `qemu-system-aarch64` is on the system `PATH`. See the [debug design docs](docs/docs/design/debug/overview.md) for full details.

For quick runs without debugging, use the terminal commands below; run regression tests after stabilizing changes:

```bash
# ArceOS (no extra preparation needed)
cargo xtask arceos qemu --package ax-helloworld --arch aarch64

# StarryOS (rootfs required on first run)
cargo xtask starry rootfs --arch aarch64    # only needed once
cargo xtask starry qemu --arch aarch64

# Axvisor (setup script checks guest images automatically)
cargo xtask axvisor qemu --arch aarch64

# Regression tests
cargo xtask arceos test qemu --target aarch64      # ArceOS
cargo xtask starry test qemu --target aarch64       # StarryOS
cargo xtask axvisor test qemu --target aarch64      # Axvisor
cargo xtask test                                    # full regression
```

## 5. License

The repository as a whole is licensed under `Apache-2.0`. Individual components may also include their own LICENSE files; when in doubt, use the files in each component directory as the source of truth.
