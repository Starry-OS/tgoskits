# Soil Protocol V1

本文档冻结第 38 轮 `KernelSoil / ExecutionHost / Worker` 契约。第 38 轮只定义可编译、可测试、可追踪的执行接口，不接入真实 syscall / driver / NPU。

## 边界

```text
Scheduler -> Worker -> KernelSoil -> ExecutionHost
```

- `Scheduler` 后续只调度 Worker，不直接执行 KernelSoil。
- `Worker` 是 Tree 能力的运行实例，不是权威事实源。
- `KernelSoil` 是唯一请求入口。
- `ExecutionHost` 是唯一执行宿主。
- `KernelSoil / Worker / ExecutionHost` 都不直接写 `GeneBank`。
- 执行反馈后续必须经过 `Sheng / State Generation Protocol` 才能成为权威事实。

## ExecutionMode

```text
MOCK
QEMU
REAL
```

第 38 轮只要求 `MOCK` 可运行。`QEMU` 在第 39-42 轮强化。`REAL` 必须等 RK3588 能力、manifest 和 latency baseline 具备后才能启用。

## SoilOperation

```text
Kernel.Time.Sleep
Driver.Serial.Write
Driver.Rknpu.Submit
Driver.Rknpu.WaitIrq
Driver.Dma.Alloc
Kernel.Ioctl
```

第 39 轮可以在不破坏 V1 契约的前提下增加 `SyscallInvoke / DriverIoctl / NpuSubmit` 的语义映射；新增枚举或破坏字段必须升协议版本。

## SoilRequest

必须包含：

```text
id
operation
gate_trace
payload
route_id
dry_run
mode
```

`Reject / Defer / Freeze / Seal` 不允许进入 `ExecutionHost`。

## SoilResult

必须包含：

```text
request_id
status
latency_us
trace
dry_run
error_code
trace_id
mode
```

不允许 silent success。失败、拒绝、阻塞和超时都必须有结构化 `error_code` 与 trace。
