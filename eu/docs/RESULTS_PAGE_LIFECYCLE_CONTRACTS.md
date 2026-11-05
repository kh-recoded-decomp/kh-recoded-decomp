# Results page task, states and display managers

This document records 9 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The outer results TaskObject and the page-state dispatcher have different result protocols. The outer holding state returns signed -1 to retain its state. The page's state-0 callback returns literal 0; its optional interface callback is a separate zero-return entrypoint. A page result of zero keeps the outer waiter pending, while a nonzero page result opens field-menu mode 2 and selects outer state 4. The human-facing meaning of mode 2 is not assigned here.

`UpdateResultsPageAndSprites` saves the page handler's result, updates both display managers regardless of that result, then returns the saved word. The managers begin at work +0x40 with stride 0x6434. Their update uses `UpdateDisplayObjectListQueued`, which writes OAM, ticks enabled cell animations and queues the OAM transfer. It allocates no manager or pool.

Task creation instantiates the overlay038 descriptor. Display setup forwards to `InitDisplayForScene`, after the constructor loads overlay027 and completion statistics. Resource initialization loads messages/graphics, initializes sprite managers and sets the initial page/exit state. That helper does not create the outer TaskObject. The work and its managers remain owned by the enclosing results task.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov038:020ba588` | ARM | `func_ov038_020ba588` | `WaitResultsPageThenOpenFieldMenu` | [eu/src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c](../src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c) |
| `ov038:020ba614` | ARM | `func_ov038_020ba614` | `ResultsTaskStateHold` | [eu/src/overlays/ov038/auto/ResultsTaskStateHold.c](../src/overlays/ov038/auto/ResultsTaskStateHold.c) |
| `ov038:020ba61c` | ARM | `func_ov038_020ba61c` | `CreateResultsPageTask` | [eu/src/overlays/ov038/calls/CreateResultsPageTask.c](../src/overlays/ov038/calls/CreateResultsPageTask.c) |
| `ov038:020ba6f8` | ARM | `func_ov038_020ba6f8` | `ResultsPageHandlerNoOp` | [eu/src/overlays/ov038/auto/ResultsPageHandlerNoOp.c](../src/overlays/ov038/auto/ResultsPageHandlerNoOp.c) |
| `ov038:020ba780` | ARM | `func_ov038_020ba780` | `ResultsPageStateNoOp` | [eu/src/overlays/ov038/auto/ResultsPageStateNoOp.c](../src/overlays/ov038/auto/ResultsPageStateNoOp.c) |
| `ov038:020bb124` | ARM | `InitOv038SlotPools` | `UpdateResultsPageSpriteManagers` | [eu/src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c](../src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c) |
| `ov038:020bbcb0` | ARM | `func_ov038_020bbcb0` | `SetupResultsPageDisplay` | [eu/src/overlays/ov038/calls/SetupResultsPageDisplay.c](../src/overlays/ov038/calls/SetupResultsPageDisplay.c) |
| `ov038:020bbcbc` | ARM | `func_ov038_020bbcbc` | `InitResultsPageResources` | [eu/src/overlays/ov038/calls/InitResultsPageResources.c](../src/overlays/ov038/calls/InitResultsPageResources.c) |
| `ov038:020bbd08` | ARM | `func_ov038_020bbd08` | `UpdateResultsPageAndSprites` | [eu/src/overlays/ov038/calls/UpdateResultsPageAndSprites.c](../src/overlays/ov038/calls/UpdateResultsPageAndSprites.c) |

## WaitResultsPageThenOpenFieldMenu

Identity: `ov038:020ba588`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov038_020ba588`.

EU entrypoint: [eu/src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c](../src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c).

```c
u32 WaitResultsPageThenOpenFieldMenu(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Updates the results page; on a nonzero page-handler result opens field menu mode2 and returns outer state4. Source: [eu/src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c:1-15](../src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c).
- The polled helper dispatches the page handler and updates both sprite managers. Source: [eu/src/overlays/ov038/calls/UpdateResultsPageAndSprites.c:1-17](../src/overlays/ov038/calls/UpdateResultsPageAndSprites.c).

Contract limits:

- Returns -1 while the page handler returns zero.
- The exact human-facing meaning of field menu mode2 is not asserted.

## ResultsTaskStateHold

Identity: `ov038:020ba614`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov038_020ba614`.

EU entrypoint: [eu/src/overlays/ov038/auto/ResultsTaskStateHold.c](../src/overlays/ov038/auto/ResultsTaskStateHold.c).

```c
u32 ResultsTaskStateHold(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns -1 with no side effects. Source: [src/ov038/leaf_research/func_ov038_020ba5f4.c:1-5](../../src/ov038/leaf_research/func_ov038_020ba5f4.c).
- Used by the outer results task state table. Source: [eu/src/overlays/ov038/data/tables/gResultsSoundStateHandlers.c:1-17](../src/overlays/ov038/data/tables/gResultsSoundStateHandlers.c).

Contract limits:

- The outer state dispatcher interprets negative return as preserving the state.

## CreateResultsPageTask

Identity: `ov038:020ba61c`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov038_020ba61c`.

EU entrypoint: [eu/src/overlays/ov038/calls/CreateResultsPageTask.c](../src/overlays/ov038/calls/CreateResultsPageTask.c).

```c
void CreateResultsPageTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Creates/stores a task from the ov038 descriptor with the caller argument. Source: [src/ov038/reviewed_helpers/func_ov038_020ba5fc.c:1-7](../../src/ov038/reviewed_helpers/func_ov038_020ba5fc.c).
- Installed as the interface start callback. Source: [eu/src/overlays/ov038/calls/InitOv038HandlerTable.c:1-10](../src/overlays/ov038/calls/InitOv038HandlerTable.c).

Contract limits:

- The old sound-context names do not imply that this task only manages audio.

## ResultsPageHandlerNoOp

Identity: `ov038:020ba6f8`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov038_020ba6f8`.

EU entrypoint: [eu/src/overlays/ov038/auto/ResultsPageHandlerNoOp.c](../src/overlays/ov038/auto/ResultsPageHandlerNoOp.c).

```c
u32 ResultsPageHandlerNoOp(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns zero without side effects. Source: [src/ov038/leaf_research/func_ov038_020ba6d8.c:1-5](../../src/ov038/leaf_research/func_ov038_020ba6d8.c).
- Installed as optional interface slot7. Source: [src/ov038/reviewed_helpers/InitOv038HandlerTable_020ba6f8.c:1-35](../../src/ov038/reviewed_helpers/InitOv038HandlerTable_020ba6f8.c).

Contract limits:

- No pause behavior is inferred from an old private field label.

## ResultsPageStateNoOp

Identity: `ov038:020ba780`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov038_020ba780`.

EU entrypoint: [eu/src/overlays/ov038/auto/ResultsPageStateNoOp.c](../src/overlays/ov038/auto/ResultsPageStateNoOp.c).

```c
u32 ResultsPageStateNoOp(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns zero without side effects. Source: [src/ov038/leaf_research/func_ov038_020ba760.c:1-5](../../src/ov038/leaf_research/func_ov038_020ba760.c).
- Occupies results page state0. Source: [eu/src/overlays/ov038/data/tables/gResultsPageStateHandlers.c:1-15](../src/overlays/ov038/data/tables/gResultsPageStateHandlers.c).

Contract limits:

- This is distinct from the outer task holding callback, which returns -1.

## UpdateResultsPageSpriteManagers

Identity: `ov038:020bb124`, ARM, native extent 56 bytes (including any configured pool). Previous symbol: `InitOv038SlotPools`.

EU entrypoint: [eu/src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c](../src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c).

```c
void UpdateResultsPageSpriteManagers(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Walks two display managers at results-work+0x40 with stride0x6434 and updates each through the queued OAM adapter. Source: [src/ov038/unclassified_helpers/InitOv038SlotPools_020bb104.c:1-17](../../src/ov038/unclassified_helpers/InitOv038SlotPools_020bb104.c).
- The EU target invokes DispObjList_Update(manager,0). Source: [eu/src/calls/UpdateDisplayObjectListQueued.c:1-3](../src/calls/UpdateDisplayObjectListQueued.c).
- Writes OAM for visible objects, ticks enabled cell animations and flushes via OamBuffer_Flush. Source: [src/arm9/shared_engine/DispObjList_Update_0204ed34.c:1-50](../../src/arm9/shared_engine/DispObjList_Update_0204ed34.c).

Contract limits:

- The old name incorrectly suggested allocation/initialization of pools.
- Managers remain allocated; this is a frame update.

## SetupResultsPageDisplay

Identity: `ov038:020bbcb0`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov038_020bbcb0`.

EU entrypoint: [eu/src/overlays/ov038/calls/SetupResultsPageDisplay.c](../src/overlays/ov038/calls/SetupResultsPageDisplay.c).

```c
void * SetupResultsPageDisplay();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Forwards to InitDisplayForScene. Source: [src/ov038/library_nitro_pxi/PXI_Init_020bbc90.c:1-5](../../src/ov038/library_nitro_pxi/PXI_Init_020bbc90.c).
- The results task constructor invokes this after loading overlay27 and completion statistics. Source: [eu/src/overlays/ov038/calls/StartOv038SoundCtx.c:1-43](../src/overlays/ov038/calls/StartOv038SoundCtx.c).

Contract limits:

- Not a PXI operation despite the shared source name.

## InitResultsPageResources

Identity: `ov038:020bbcbc`, ARM, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov038_020bbcbc`.

EU entrypoint: [eu/src/overlays/ov038/calls/InitResultsPageResources.c](../src/overlays/ov038/calls/InitResultsPageResources.c).

```c
void InitResultsPageResources(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Loads message containers and graphics, initializes sprite managers, then sets the initial exit/page state through ResetOv038ExitState(1). Source: [eu/src/overlays/ov038/calls/InitResultsPageResources.c:1-13](../src/overlays/ov038/calls/InitResultsPageResources.c).

Contract limits:

- This does not create the outer TaskObject.

## UpdateResultsPageAndSprites

Identity: `ov038:020bbd08`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov038_020bbd08`.

EU entrypoint: [eu/src/overlays/ov038/calls/UpdateResultsPageAndSprites.c](../src/overlays/ov038/calls/UpdateResultsPageAndSprites.c).

```c
unsigned int UpdateResultsPageAndSprites(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Dispatches the current page-state handler, updates both sprite managers and returns the saved handler result. Source: [eu/src/overlays/ov038/calls/UpdateResultsPageAndSprites.c:1-17](../src/overlays/ov038/calls/UpdateResultsPageAndSprites.c).
- The callee walks two0x6434-byte display managers and forwards each to the queued object-list update adapter. Source: [src/ov038/unclassified_helpers/InitOv038SlotPools_020bb104.c:1-17](../../src/ov038/unclassified_helpers/InitOv038SlotPools_020bb104.c).
- EU resolves the apparent NNS list initializer to DispObjList_Update, not list initialization. Source: [eu/src/calls/UpdateDisplayObjectListQueued.c:1-3](../src/calls/UpdateDisplayObjectListQueued.c).

Contract limits:

- Sprites update even if page handler returns zero.
- No state-index bounds check is added.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov038/calls/WaitResultsPageThenOpenFieldMenu.c WaitResultsPageThenOpenFieldMenu
python tools/verify_idx.py src/overlays/ov038/auto/ResultsTaskStateHold.c ResultsTaskStateHold
python tools/verify_idx.py src/overlays/ov038/calls/CreateResultsPageTask.c CreateResultsPageTask
python tools/verify_idx.py src/overlays/ov038/auto/ResultsPageHandlerNoOp.c ResultsPageHandlerNoOp
python tools/verify_idx.py src/overlays/ov038/auto/ResultsPageStateNoOp.c ResultsPageStateNoOp
python tools/verify_idx.py src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c UpdateResultsPageSpriteManagers
python tools/verify_idx.py src/overlays/ov038/calls/SetupResultsPageDisplay.c SetupResultsPageDisplay
python tools/verify_idx.py src/overlays/ov038/calls/InitResultsPageResources.c InitResultsPageResources
python tools/verify_idx.py src/overlays/ov038/calls/UpdateResultsPageAndSprites.c UpdateResultsPageAndSprites
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The full
108-function block passes the fresh gate for all 108 linked modules. Affected
function bytes, resolved relocation targets/types and addends, and all module
hashes match the preserved baseline. Native signatures and algorithms are
unchanged; verified-library receipts remain current.
