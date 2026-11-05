# Continue scene lifecycle helpers

This document records 4 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The continue interface creates a TaskObject from overlay037's descriptor, stores its handle and keeps a separate scene-work owner. Readiness is false without work and otherwise tests that initialization flag 1 has cleared. The owner is initialized with flags 3 and the initialization path clears bit 1 after preparing the continue context when needed. The predicate does not test shutdown or wireless state.

The billboard adapter forwards to the actor-slot/billboard update and is called from this scene's frame path. Its old PXI source label establishes no FIFO operation or result contract. The actor-callback tick supplies 0x1000, one fixed-point unit with 12 fractional bits; the helper does not measure elapsed wall time. Neither update helper creates or frees the scene work.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov037:020baa84` | ARM | `func_ov037_020baa84` | `UpdateContinueActorBillboards` | [eu/src/overlays/ov037/calls/UpdateContinueActorBillboards.c](../src/overlays/ov037/calls/UpdateContinueActorBillboards.c) |
| `ov037:020baa90` | ARM | `func_ov037_020baa90` | `TickContinueActorCallbacks` | [eu/src/overlays/ov037/calls/TickContinueActorCallbacks.c](../src/overlays/ov037/calls/TickContinueActorCallbacks.c) |
| `ov037:020bab98` | ARM | `func_ov037_020bab98` | `CreateContinueSceneTask` | [eu/src/overlays/ov037/calls/CreateContinueSceneTask.c](../src/overlays/ov037/calls/CreateContinueSceneTask.c) |
| `ov037:020babbc` | ARM | `func_ov037_020babbc` | `IsContinueSceneReady` | [eu/src/overlays/ov037/calls/IsContinueSceneReady.c](../src/overlays/ov037/calls/IsContinueSceneReady.c) |

## UpdateContinueActorBillboards

Identity: `ov037:020baa84`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov037_020baa84`.

EU entrypoint: [eu/src/overlays/ov037/calls/UpdateContinueActorBillboards.c](../src/overlays/ov037/calls/UpdateContinueActorBillboards.c).

```c
void * UpdateContinueActorBillboards();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Forwards to UpdateActorSlotsAndBillboards. Source: [src/ov037/library_nitro_pxi/PXI_Init_020baa64.c:1-5](../../src/ov037/library_nitro_pxi/PXI_Init_020baa64.c).
- The continue-scene task uses this wrapper in its frame update path. Source: [eu/src/overlays/ov037/calls/RunCommStepMachine.c:1-6](../src/overlays/ov037/calls/RunCommStepMachine.c).

Contract limits:

- Not a PXI initialization despite shared source label.

## TickContinueActorCallbacks

Identity: `ov037:020baa90`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov037_020baa90`.

EU entrypoint: [eu/src/overlays/ov037/calls/TickContinueActorCallbacks.c](../src/overlays/ov037/calls/TickContinueActorCallbacks.c).

```c
void TickContinueActorCallbacks(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls ActorRegistry_ForEachCallback with fixed-point step0x1000. Source: [eu/src/overlays/ov037/calls/TickContinueActorCallbacks.c:1-7](../src/overlays/ov037/calls/TickContinueActorCallbacks.c).
- Installs this callback in the continue interface. Source: [eu/src/overlays/ov037/calls/InitCommHandlerTable.c:1-10](../src/overlays/ov037/calls/InitCommHandlerTable.c).

Contract limits:

- Uses a fixed unit step; no elapsed real-time unit is inferred.

## CreateContinueSceneTask

Identity: `ov037:020bab98`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov037_020bab98`.

EU entrypoint: [eu/src/overlays/ov037/calls/CreateContinueSceneTask.c](../src/overlays/ov037/calls/CreateContinueSceneTask.c).

```c
void CreateContinueSceneTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Creates a task from the ov037 descriptor and caller argument, storing the handle. Source: [src/ov037/reviewed_helpers/func_ov037_020bab78.c:1-7](../../src/ov037/reviewed_helpers/func_ov037_020bab78.c).
- The continue interface installs this function as task creation callback. Source: [eu/src/overlays/ov037/calls/InitCommHandlerTable.c:1-10](../src/overlays/ov037/calls/InitCommHandlerTable.c).

Contract limits:

- Task handle and gContinueSceneState work are separate owners.

## IsContinueSceneReady

Identity: `ov037:020babbc`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov037_020babbc`.

EU entrypoint: [eu/src/overlays/ov037/calls/IsContinueSceneReady.c](../src/overlays/ov037/calls/IsContinueSceneReady.c).

```c
BOOL IsContinueSceneReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false for absent continue work and otherwise tests initialization flag1 clear. Source: [eu/src/overlays/ov037/calls/IsContinueSceneReady.c:1-19](../src/overlays/ov037/calls/IsContinueSceneReady.c).
- Creates this owner and initializes flags3. Source: [src/ov037/unclassified_helpers/BeginCommSession_020ba3e0.c:1-40](../../src/ov037/unclassified_helpers/BeginCommSession_020ba3e0.c).
- Clears flag1 while completing initialization and creates the continue-menu context when needed. Source: [eu/src/overlays/ov037/calls/FinishCommSession.c:1-33](../src/overlays/ov037/calls/FinishCommSession.c).

Contract limits:

- Does not test shutdown completion or wireless state.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov037/calls/UpdateContinueActorBillboards.c UpdateContinueActorBillboards
python tools/verify_idx.py src/overlays/ov037/calls/TickContinueActorCallbacks.c TickContinueActorCallbacks
python tools/verify_idx.py src/overlays/ov037/calls/CreateContinueSceneTask.c CreateContinueSceneTask
python tools/verify_idx.py src/overlays/ov037/calls/IsContinueSceneReady.c IsContinueSceneReady
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The full
108-function block passes the fresh gate for all 108 linked modules. Affected
function bytes, resolved relocation targets/types and addends, and all module
hashes match the preserved baseline. Native signatures and algorithms are
unchanged; verified-library receipts remain current.
