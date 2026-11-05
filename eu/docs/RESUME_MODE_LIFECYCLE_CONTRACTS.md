# Resume mode task and result contracts

This document records 13 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The resume TaskObject and resume context are separate owners. Creation instantiates the descriptor and stores the task handle. Its constructor initializes state 0 and returns the state-machine method. That dispatcher clears repeat bit 0x8000, invokes the indexed handler, stores a nonnegative next state and repeats when the handler sets the bit. A signed negative result retains the state; the holding entry returns -1. Native state indexing remains unchecked.

Readiness is false without context and otherwise means flag 1 has cleared after starting the resume overlay. Completion stores the caller's word at context +0x10 and sets 0x4000. The waiting state always performs one menu update before testing completion. The result getter has no readiness check. These result words are not assigned story/menu meanings.

Finishing shuts down the active overlay, restores sound/panel state, conditionally applies the supplied field-resume parameters, releases the sequence heap and sets the task +0x28 signal. The signal getter normalizes nonzero, but does not test scheduler state -2 or destroy the task. Explicit destruction uses `DestroyTaskObjectWrapper` and invalidates the saved handle with -1; no validity guard is added. Optional callback slot 7 returns literal zero and is deliberately inert.

The completion adapter forwards its live result argument despite a no-argument/PXI source label; its semantic operation is the void completion setter. The protection helper separately invokes a nonnull callback and returns the bitwise inverse of its address, not the callback's result. It preserves existing protection behavior.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov033:020ba400` | ARM | `func_ov033_020ba400` | `InvokeProtectionCallbackAndInvertAddress` | [eu/src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c](../src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c) |
| `ov033:020ba574` | ARM | `func_ov033_020ba574` | `RunResumeModeStateMachine` | [eu/src/overlays/ov033/calls/RunResumeModeStateMachine.c](../src/overlays/ov033/calls/RunResumeModeStateMachine.c) |
| `ov033:020ba71c` | ARM | `func_ov033_020ba71c` | `UpdateResumeMenuUntilResult` | [eu/src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c](../src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c) |
| `ov033:020ba74c` | ARM | `func_ov033_020ba74c` | `FinishResumeMenuAndRestoreField` | [eu/src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c](../src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c) |
| `ov033:020ba7f0` | ARM | `func_ov033_020ba7f0` | `ResumeModeStateHold` | [eu/src/overlays/ov033/auto/ResumeModeStateHold.c](../src/overlays/ov033/auto/ResumeModeStateHold.c) |
| `ov033:020ba8f4` | ARM | `func_ov033_020ba8f4` | `CreateResumeModeTask` | [eu/src/overlays/ov033/calls/CreateResumeModeTask.c](../src/overlays/ov033/calls/CreateResumeModeTask.c) |
| `ov033:020ba918` | ARM | `func_ov033_020ba918` | `IsResumeModeReady` | [eu/src/overlays/ov033/calls/IsResumeModeReady.c](../src/overlays/ov033/calls/IsResumeModeReady.c) |
| `ov033:020ba968` | ARM | `func_ov033_020ba968` | `CompleteResumeModeWithResult` | [eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c](../src/overlays/ov033/calls/CompleteResumeModeWithResult.c) |
| `ov033:020ba98c` | ARM | `func_ov033_020ba98c` | `HasResumeModeTaskExitSignal` | [eu/src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c](../src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c) |
| `ov033:020ba9b0` | ARM | `func_ov033_020ba9b0` | `DestroyResumeModeTask` | [eu/src/overlays/ov033/calls/DestroyResumeModeTask.c](../src/overlays/ov033/calls/DestroyResumeModeTask.c) |
| `ov033:020ba9d0` | ARM | `func_ov033_020ba9d0` | `ResumeModeNoOpCallback` | [eu/src/overlays/ov033/auto/ResumeModeNoOpCallback.c](../src/overlays/ov033/auto/ResumeModeNoOpCallback.c) |
| `ov033:020ba9d8` | ARM | `func_ov033_020ba9d8` | `GetResumeModeResult` | [eu/src/overlays/ov033/calls/GetResumeModeResult.c](../src/overlays/ov033/calls/GetResumeModeResult.c) |
| `ov033:020baa60` | ARM | `func_ov033_020baa60` | `CompleteResumeModeWithResultAdapter` | [eu/src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c](../src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c) |

## InvokeProtectionCallbackAndInvertAddress

Identity: `ov033:020ba400`, ARM, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov033_020ba400`.

EU entrypoint: [eu/src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c](../src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c).

```c
u32 InvokeProtectionCallbackAndInvertAddress(Callback callback);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Invokes a nonnull callback, then returns the bitwise inverse of its address. Source: [eu/src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c:1-11](../src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c).
- Passes this exact function to the protection detectors and compares the result against the inverse callback pointer. Source: [eu/src/overlays/ov033/calls/InitResumeModeContext.c:1-68](../src/overlays/ov033/calls/InitResumeModeContext.c).

Contract limits:

- The return is an inverted callback address, not the callback return value.
- Records existing protection behavior; does not remove or bypass it.

## RunResumeModeStateMachine

Identity: `ov033:020ba574`, ARM, native extent 96 bytes (including any configured pool). Previous symbol: `func_ov033_020ba574`.

EU entrypoint: [eu/src/overlays/ov033/calls/RunResumeModeStateMachine.c](../src/overlays/ov033/calls/RunResumeModeStateMachine.c).

```c
u32 RunResumeModeStateMachine(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Clears repeat flag0x8000, dispatches gResumeModeHandlers[state], stores nonnegative next state, and repeats if the handler sets the repeat flag. Source: [eu/src/overlays/ov033/calls/RunResumeModeStateMachine.c:1-27](../src/overlays/ov033/calls/RunResumeModeStateMachine.c).
- Initializes state0 and returns this function as the task update callback. Source: [eu/src/overlays/ov033/calls/InitResumeModeContext.c:1-68](../src/overlays/ov033/calls/InitResumeModeContext.c).

Contract limits:

- Negative handler return preserves the existing state.
- Does not bounds-check the state index.

## UpdateResumeMenuUntilResult

Identity: `ov033:020ba71c`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov033_020ba71c`.

EU entrypoint: [eu/src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c](../src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c).

```c
u32 UpdateResumeMenuUntilResult(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Runs UpdateOverlayFrame(0); returns state2 once resume-context flag0x4000 is set, otherwise -1. Source: [eu/src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c:1-21](../src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c).
- The paired completion function stores the result and sets exactly flag0x4000. Source: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c:1-16](../src/overlays/ov033/calls/CompleteResumeModeWithResult.c).

Contract limits:

- Always performs one menu update before checking completion.

## FinishResumeMenuAndRestoreField

Identity: `ov033:020ba74c`, ARM, native extent 164 bytes (including any configured pool). Previous symbol: `func_ov033_020ba74c`.

EU entrypoint: [eu/src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c](../src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c).

```c
unsigned int FinishResumeMenuAndRestoreField(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Shuts down the active overlay, restores BGM/panel state, conditionally applies resume field parameters, releases the sequence heap and marks the task exit signal; schedules state3. Source: [eu/src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c:1-33](../src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c).
- The owner holds resume position/mode parameters supplied at creation. Source: [eu/src/overlays/ov033/calls/InitResumeModeContext.c:1-68](../src/overlays/ov033/calls/InitResumeModeContext.c).

Contract limits:

- The existing session flag controls whether field parameters and session bit are updated.
- Does not infer a human-facing name for mode6 or mode3.

## ResumeModeStateHold

Identity: `ov033:020ba7f0`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov033_020ba7f0`.

EU entrypoint: [eu/src/overlays/ov033/auto/ResumeModeStateHold.c](../src/overlays/ov033/auto/ResumeModeStateHold.c).

```c
u32 ResumeModeStateHold(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns -1 without state changes. Source: [src/ov033/leaf_research/func_ov033_020ba7d0.c:1-5](../../src/ov033/leaf_research/func_ov033_020ba7d0.c).
- The function occupies the terminal/holding entry of the state handler table. Source: [eu/src/overlays/ov033/data/tables/gResumeModeHandlers.c:1-13](../src/overlays/ov033/data/tables/gResumeModeHandlers.c).
- The dispatcher leaves its state unchanged for negative handler results. Source: [eu/src/overlays/ov033/calls/RunResumeModeStateMachine.c:1-27](../src/overlays/ov033/calls/RunResumeModeStateMachine.c).

Contract limits:

- Preserves a separate entrypoint despite the trivial implementation.

## CreateResumeModeTask

Identity: `ov033:020ba8f4`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov033_020ba8f4`.

EU entrypoint: [eu/src/overlays/ov033/calls/CreateResumeModeTask.c](../src/overlays/ov033/calls/CreateResumeModeTask.c).

```c
void CreateResumeModeTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls CreateTaskObject with the resume descriptor and caller argument, storing the resulting task handle. Source: [src/ov033/reviewed_helpers/func_ov033_020ba8d4.c:1-7](../../src/ov033/reviewed_helpers/func_ov033_020ba8d4.c).
- Installs this exact function in create handler slot0. Source: [eu/src/overlays/ov033/calls/InstallResumeModeHandlers.c:1-30](../src/overlays/ov033/calls/InstallResumeModeHandlers.c).

Contract limits:

- The task object and its work/context pointer are different allocations/owners.

## IsResumeModeReady

Identity: `ov033:020ba918`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov033_020ba918`.

EU entrypoint: [eu/src/overlays/ov033/calls/IsResumeModeReady.c](../src/overlays/ov033/calls/IsResumeModeReady.c).

```c
BOOL IsResumeModeReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false for null context, otherwise whether flag0x01 is clear. Source: [eu/src/overlays/ov033/calls/IsResumeModeReady.c:1-19](../src/overlays/ov033/calls/IsResumeModeReady.c).
- Initializes flags to3 before the mode begins. Source: [eu/src/overlays/ov033/calls/InitResumeModeContext.c:1-68](../src/overlays/ov033/calls/InitResumeModeContext.c).
- Clears flag1 only after starting the resume overlay successfully. Source: [eu/src/overlays/ov033/calls/BeginResumeMode.c:1-48](../src/overlays/ov033/calls/BeginResumeMode.c).

Contract limits:

- Readiness is this explicit lifecycle flag; does not imply every child resource is loaded.

## CompleteResumeModeWithResult

Identity: `ov033:020ba968`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov033_020ba968`.

EU entrypoint: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c](../src/overlays/ov033/calls/CompleteResumeModeWithResult.c).

```c
void CompleteResumeModeWithResult(u32 value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores the supplied result at context+0x10 and sets completion flag0x4000. Source: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c:1-16](../src/overlays/ov033/calls/CompleteResumeModeWithResult.c).
- The update state observes flag0x4000 and advances to completion processing. Source: [eu/src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c:1-21](../src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c).

Contract limits:

- Does not immediately tear down the overlay or task.

## HasResumeModeTaskExitSignal

Identity: `ov033:020ba98c`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov033_020ba98c`.

EU entrypoint: [eu/src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c](../src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c).

```c
BOOL HasResumeModeTaskExitSignal(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads task+0x28 through Obj_GetWord28 and returns whether nonzero. Source: [eu/src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c:1-9](../src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c).
- The finish path explicitly writes the current task signal through StoreToGlobalPtr4Field28(1). Source: [eu/src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c:1-33](../src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c).
- Stores the caller word at current task+0x28. Source: [src/arm9/shared_engine/StoreToGlobalPtr4Field28_0202a778.c:1-5](../../src/arm9/shared_engine/StoreToGlobalPtr4Field28_0202a778.c).

Contract limits:

- Does not poll TaskObject state -2 or destroy the task.
- The signal value is tested for nonzero, not equality to1.

## DestroyResumeModeTask

Identity: `ov033:020ba9b0`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov033_020ba9b0`.

EU entrypoint: [eu/src/overlays/ov033/calls/DestroyResumeModeTask.c](../src/overlays/ov033/calls/DestroyResumeModeTask.c).

```c
void DestroyResumeModeTask(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Destroys the stored task via the real DestroyTaskObjectWrapper callee and sets its handle to -1. Source: [eu/src/overlays/ov033/calls/DestroyResumeModeTask.c:1-10](../src/overlays/ov033/calls/DestroyResumeModeTask.c).
- Installed as handler slot5 in the resume interface. Source: [eu/src/overlays/ov033/calls/InstallResumeModeHandlers.c:1-30](../src/overlays/ov033/calls/InstallResumeModeHandlers.c).

Contract limits:

- The old PXI label of the target is false; this is task destruction.
- No null/invalid handle check is added.

## ResumeModeNoOpCallback

Identity: `ov033:020ba9d0`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov033_020ba9d0`.

EU entrypoint: [eu/src/overlays/ov033/auto/ResumeModeNoOpCallback.c](../src/overlays/ov033/auto/ResumeModeNoOpCallback.c).

```c
u32 ResumeModeNoOpCallback(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns zero with no side effects. Source: [src/ov033/leaf_research/func_ov033_020ba9b0.c:1-5](../../src/ov033/leaf_research/func_ov033_020ba9b0.c).
- Installed as optional callback slot7. Source: [eu/src/overlays/ov033/calls/InstallResumeModeHandlers.c:1-30](../src/overlays/ov033/calls/InstallResumeModeHandlers.c).

Contract limits:

- The callback is intentionally inert; no sound or filesystem semantics are inferred.

## GetResumeModeResult

Identity: `ov033:020ba9d8`, ARM, native extent 20 bytes (including any configured pool). Previous symbol: `func_ov033_020ba9d8`.

EU entrypoint: [eu/src/overlays/ov033/calls/GetResumeModeResult.c](../src/overlays/ov033/calls/GetResumeModeResult.c).

```c
int GetResumeModeResult(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns context+0x10. Source: [eu/src/overlays/ov033/calls/GetResumeModeResult.c:1-5](../src/overlays/ov033/calls/GetResumeModeResult.c).
- The completion setter stores the result at the exact same word. Source: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c:1-16](../src/overlays/ov033/calls/CompleteResumeModeWithResult.c).

Contract limits:

- No ready/completion check is performed.

## CompleteResumeModeWithResultAdapter

Identity: `ov033:020baa60`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov033_020baa60`.

EU entrypoint: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c](../src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c).

```c
void * CompleteResumeModeWithResultAdapter();
```

The empty argument list and pointer result are legacy forwarding views. The logical operation takes the completion-result word and has the void setter's semantics; no pointer ownership is established.

Demonstrated behavior and evidence:

- Tail-forwards live registers to CompleteResumeModeWithResult. Source: [src/ov033/library_nitro_pxi/PXI_Init_020baa40.c:1-5](../../src/ov033/library_nitro_pxi/PXI_Init_020baa40.c).
- EU aliases the apparent PXI_InitFifo callee to the completion setter. Source: [eu/src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c:1-3](../src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c).

Contract limits:

- The real logical input is the result word; the shared no-argument declaration omits live R0.
- No PXI FIFO operation occurs.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov033/calls/InvokeProtectionCallbackAndInvertAddress.c InvokeProtectionCallbackAndInvertAddress
python tools/verify_idx.py src/overlays/ov033/calls/RunResumeModeStateMachine.c RunResumeModeStateMachine
python tools/verify_idx.py src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c UpdateResumeMenuUntilResult
python tools/verify_idx.py src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c FinishResumeMenuAndRestoreField
python tools/verify_idx.py src/overlays/ov033/auto/ResumeModeStateHold.c ResumeModeStateHold
python tools/verify_idx.py src/overlays/ov033/calls/CreateResumeModeTask.c CreateResumeModeTask
python tools/verify_idx.py src/overlays/ov033/calls/IsResumeModeReady.c IsResumeModeReady
python tools/verify_idx.py src/overlays/ov033/calls/CompleteResumeModeWithResult.c CompleteResumeModeWithResult
python tools/verify_idx.py src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c HasResumeModeTaskExitSignal
python tools/verify_idx.py src/overlays/ov033/calls/DestroyResumeModeTask.c DestroyResumeModeTask
python tools/verify_idx.py src/overlays/ov033/auto/ResumeModeNoOpCallback.c ResumeModeNoOpCallback
python tools/verify_idx.py src/overlays/ov033/calls/GetResumeModeResult.c GetResumeModeResult
python tools/verify_idx.py src/overlays/ov033/calls/CompleteResumeModeWithResultAdapter.c CompleteResumeModeWithResultAdapter
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
