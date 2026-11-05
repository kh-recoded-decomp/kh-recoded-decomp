# EU semantic names and recovered layouts

Names are accepted from behavior, callers and data layout, not from a desired
coverage percentage. A source may retain an address-based name when its role is
uncertain. Naming does not add code or DATA reconstruction credit.

## Collision block

| Previous name | Current name | Evidence |
|---|---|---|
| `func_02047198` | `SweepSphereAgainstRim` | The matched C translates a sphere center into a rim basis, forms quartic coefficients, selects a distance and returns a contact normal. `SweepSphereAgainstCappedCylinder` calls it for each cylinder endpoint; `SweepCylinderAgainstCylinder` also uses the endpoint-rim operation. |
| `func_02034d78` | `ProjectMotionAgainstContactNormals` | Its two real inputs are a mutable motion vector and the recovered contacts workspace. `projectionMode` selects unchanged motion, plane/crease projection or a zero result. It is used from contact push-out and the field/world sweep callers. The existing ARM/C/model tests cover its mode and threshold behavior. |
| `func_01ffb4f8` | `ResolveCollisionTreeContacts` | Its three inputs supply the initial node, mover query and collision model. It visits explicit faces and quadtree candidates, records planes, performs the enabled resolve/retry path and dispatches contact callbacks. `TestMoverAgainstModel` is its established caller; [COLLISION_TRAVERSAL.md](COLLISION_TRAVERSAL.md) records modes, ownership and outputs. |
| `data_027e00b0` | `gCollisionTraversalTop` | `ResetCollTraversal` writes the frame base; traversal reads the current frame, stores its successor on descent and stores a parent frame while backtracking. `FindQuadTreeContact` uses the same cursor through its EU wrapper. |
| `data_027e00b4` | `gCollisionTraversalFrames` | Existing BSS owns exactly 128 bytes at this address. Reset initializes eight 16-byte frames; traversal accesses child index, flags and the X/Z region at the documented offsets. |

The storage definition now uses a frame pointer and an eight-element typed
array instead of a raw `u32` and a 32-word array. The source header checks the
12-byte region, 16-byte frame and four-byte DS pointer. No object size,
parameter, data address or field offset is invented to influence compilation.
The complete frame layout and shared-state/legacy-view constraints are in
[COLLISION_TRAVERSAL.md](COLLISION_TRAVERSAL.md).

Function addresses and public calling conventions remain the same. The changed
references are EU symbol/alias mappings; the shared US implementations are not
rewritten. Historical numeric names can remain in archive files and the
ROM-derived index; current configuration and source declarations use the new
names. The index is reconstructed with `tools/rebuild_index.py`, which checks
relocations against the ROM and preserves disagreeing historical entries.

The shared-source wrappers for `CollWorld_FindHitPreserveState`,
`GatherQuadtreeFaces`, `TestMoverAgainstModelTree` and
`TestMoverAgainstModelWalls` also map the two old DTCM identifiers to the new
symbols. These mappings are necessary because the included US source still
uses its original identifiers; the renaming tool's EU-only text scan cannot
see those references inside another region's source.

## Verification commands

From `eu/`:

```sh
python tools/verify_idx.py src/calls/SweepSphereAgainstRim.c SweepSphereAgainstRim
python tools/verify_idx.py src/calls/ProjectMotionAgainstContactNormals.c ProjectMotionAgainstContactNormals
python tools/verify_idx.py src/calls/ResolveCollisionTreeContacts.c ResolveCollisionTreeContacts
python tools/verify_idx.py src/calls/ResetCollTraversal.c ResetCollTraversal
python tools/verify_idx.py src/calls/FindQuadTreeContact.c FindQuadTreeContact --thumb
python tools/verify_idx.py src/calls/CollWorld_FindHitPreserveState.c CollWorld_FindHitPreserveState
python tools/verify_idx.py src/calls/GatherQuadtreeFaces.c GatherQuadtreeFaces
python tools/verify_idx.py src/calls/TestMoverAgainstModelTree.c TestMoverAgainstModelTree --thumb
python tools/verify_idx.py src/calls/TestMoverAgainstModelWalls.c TestMoverAgainstModelWalls --thumb
python tools/test_contact_motion.py -v
bash tools/gate.sh
python tools/progress.py
```

The expected function sizes are 1480, 528, 6200, 84 and 408 bytes respectively.
The four additional wrapper sizes are 276, 1828, 892 and 872 bytes. Each check
must pass the official byte/relocation verifier. The final linked gate
also checks the DATA layout and all affected callers across 108 modules.

## Documented UI operations

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020b91e8` | `SetWidgetPosition` | Six named modes update the widget's offset and send the resulting position to its indexed records. [WIDGET_POSITION.md](WIDGET_POSITION.md) documents modes, wrapping arithmetic, Y-axis asymmetry and aliasing; the existing ROM/compiled-C/model tests cover the behavior. |
| `func_ov034_020ba400` | `InitResultsScene` | Clears the task-owned results work record, copies scene arguments, obtains session parameters, initializes dependent resources, rewards and shop state, and returns `UpdateResultsScreen`. [RESULTS_SCENE.md](RESULTS_SCENE.md) records the work/parameter layouts, paired BSS views and task ownership. |

The setter's EU references are renamed together, including the declarations and
aliases used by other overlays. `InitResultsScreen` remains a different function;
its name and role are not merged with `InitResultsScene`. The ITCM name change
also needs a preprocessor mapping in the EU `TestMoverAgainstModel` wrapper,
whose included US implementation retains `func_01ffb4f8`.

From `eu/`, also run:

```sh
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetPosition.c SetWidgetPosition
python tools/verify_idx.py src/overlays/ov034/calls/InitResultsScene.c InitResultsScene
python tools/verify_idx.py src/calls/TestMoverAgainstModel.c TestMoverAgainstModel --thumb
python tools/test_widget_position.py -v
```

Those function sizes remain 408, 1972 and 344 bytes. Re-run the full gate after
the symbol changes so every caller and callback table is resolved at its
original address. This work does not change function signatures or arithmetic.

## Shared buffer operations

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov001_0206468c` | `SessionBuffer_GetAddress` | Reads the first word of an eight-byte slot; the allocator writes its returned pointer there and `InitResultsScene`/`CreateBoardScreen` consume it as a buffer address. |
| `func_ov001_020646a4` | `SessionBuffer_GetSize` | Reads the second slot word; the allocator writes the requested byte size there and the results initializer tests it before allocating its parameters. |
| `func_ov001_020646b8` | `SessionBuffer_Free` | Tests the stored address, passes the block to the actual default-heap free routine and clears the two words only on that nonzero path. |

[SESSION_BUFFERS.md](SESSION_BUFFERS.md) records the recovered slot type,
consistent caller declarations, explicit free argument and the unresolved
context/table-capacity boundary. The context itself is not renamed by inference
from one of its subobjects.

## Captured touch task

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020b9f74` | `InitCapturedTouchTask` | Descriptor initialization callback; retains current task work as the captured record and returns the update callback. |
| `func_ov027_020b9f8c` | `ShutdownCapturedTouchTask` | Descriptor shutdown callback; the two-byte Thumb implementation returns without work. |
| `func_ov027_020b9f90` | `UpdateCapturedTouchTask` | Calls the established capture routine and returns zero. The shared source's former message-queue label did not describe this EU binding. |
| `data_ov027_020ba3a0` | `gCapturedTouchTaskDescriptor` | Five-word descriptor names these callbacks and an eight-byte task work allocation; profile, HUD and overlay-39 callers pass it to the task constructor. |
| `data_ov027_020ba3e0` | `gCapturedTouchRecord` | Four-byte BSS pointer initialized from task work, filled by touch capture, copied by `CopySourceBlock` and cleared at record offset four. |

[CAPTURED_TOUCH.md](CAPTURED_TOUCH.md) records the recovered layout, selection
fallback, partial-clear behavior, task ownership, empty shutdown and legacy
copy ABI views. The neighboring queue-state storage is not folded into this
type. The initializer's ignored argument is evidenced by the actual
`Obj_Construct` call, rather than introduced to alter code generation.

## File-load queue task

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020ba060` | `InitFileLoadQueueTask` | Initializes two intrusive lists in the 24-byte task work and returns the queue update callback. |
| `func_ov027_020ba124` | `UpdateFileLoadQueueTask` | Calls `ProcessFileLoadQueue` and returns zero. |
| `func_ov027_020ba1f8` | `GetFileLoadRequestBuffer` | Reads request offset eight, written with the loader's buffer address and consumed by resource unpackers/free operations. |
| `data_ov027_020ba3b4` | `gFileLoadQueueTaskDescriptor` | The descriptor's established prefix binds the initializer, shutdown and 24-byte work allocation; its trailing zero words are retained without interpretation. |
| `data_ov027_020ba3e4` | `gFileLoadQueueStateWords` | Original seven-word BSS span; only word zero is evidenced as the task work address. The name does not assert a complete seven-field runtime structure. |

[FILE_LOAD_QUEUE.md](FILE_LOAD_QUEUE.md) records the common request/list layout,
buffer/activity-key evidence, callback ordering, ownership, partial empty
predicate, explicit getter arguments and unassigned storage boundaries.

## Main file loader

| Previous name | Current name | Evidence |
|---|---|---|
| `func_0202c378` | `RequestFileLoadFromHeapHead` | Selector zero reaches positive-32-byte-aligned destination allocation in both plain and compressed paths; the allocator selects `AllocFromHead`. |
| `func_0202c38c` | `RequestFileLoadFromHeapTail` | Selector one reaches negative-32 alignment in both paths; the allocator selects `AllocFromTail`. |
| `func_0202c44c` | `SleepIfFileLoaderBusy` | Conditionally sleeps using pending count/current request, then returns one; it is not a completion result. |
| `data_02060584` | `gFileLoaderMessageQueue` | OS initialization, file/audio producers, worker receive and the ring activity query establish the queue and its 32-byte layout. |
| `data_020605a4` | `gFileLoaderThreadStorage` | Passed to thread construction and direct wakeup; 192-byte storage retained without inferred thread fields. |
| `data_02060664` | `gFileLoaderMessages` | The queue is initialized with this backing table and a capacity of 64. |

[FILE_LOADER.md](FILE_LOADER.md) records the recovered layout, shared file/audio
use, count-word overlap, worker wake ordering, unresolved wrapper ABI views and
host pointer/thread boundaries. Shared US identifiers stay separate from EU
semantic names even when their old numeric spellings collide.

## Stage-manager flags

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov001_0209c5ac` | `GetMaskedStageManagerFlags` | Returns the selected first-word bits, or zero for an absent manager. Callers query masks in actor movement, events and script processing. |
| `func_ov001_0209c5c4` | `SetStageManagerFlagBits` | ORs the mask into the same first word, preserving all other bits. |
| `func_ov001_0209c5d8` | `ClearStageManagerFlagBits` | ANDs that word with the mask complement, preserving all other bits. |
| `AllocateActorSlotOrReportError` | `ClearStageMask30WhenBit0Clear` | Tests bit 0, conditionally clears mask `0x30` and returns 3 or 0. No allocation or error reporting occurs in this EU implementation. |

[STAGE_MANAGER_FLAGS.md](STAGE_MANAGER_FLAGS.md) records the mask-valued query,
null-manager behavior, corrected conditional-helper contract and unresolved bit
roles. The first-word field reuses the existing `StageMotionManager` view while
preserving every previously established motion offset.

## Widget indexed-record operations

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020b9604` | `ClearWidgetRecordActiveBits` | Visits two IDs at widget `+0x14`, skips `-1` and calls the indexed helper that clears mask `0x02` in record flags. |
| `func_ov027_020b9640` | `SetWidgetRecordActiveBits` | Same traversal, setting mask `0x02`. |
| `func_ov027_020b967c` | `GetWidgetAnimationFrame` | Queries the first ID other than `-1`, through the SDK current-frame index getter. |
| `func_ov027_020b96c0` | `SetWidgetAnimationFrame` | Delegates frame selection to each configured record's SDK cell animation. |
| `func_ov027_020b97d8` | `SetWidgetRecordMode` | Applies the indexed mode-word setter to both configured IDs. |
| `func_0204f23c` | `GetIndexedRecordAnimationFrame` | Uses `0x8c` stride and controller offset `0x18`; the SDK computes the current frame array index. |
| `func_0204f218` | `SetIndexedRecordAnimationFrame` | Uses the same stride/offset and reaches SDK frame-index selection rather than an elapsed-time tick. |
| `Slot_SetMode2Bit` | `SetIndexedRecordMode` | Replaces the mode word at record `+0x74` with `mode & 3`. |

[WIDGET_RECORD_OPS.md](WIDGET_RECORD_OPS.md) records sentinel/negative-index
differences, first-selected query behavior, duplicate calls, shared DS views,
explicit caller narrowing, native return words and host layout boundaries.
The existing widget position prefix and position-control implementations are
preserved. Relocation-name refresh uses ROM proof without changing indexed
bytes or the official verifier.

## Packed resources and text wrappers

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov027_020ba2c8` | `GetPackedFileEntry` | Uses the loaded view's count/payload, follows variable per-record byte strides and returns the selected payload after its four-byte prefix; it performs no text decoding. |
| `func_ov027_020ba300` | `FormatPackedWideText` | Builds the native DS variadic argument stream and delegates to the V wrapper, returning the destination. |
| `func_ov027_020ba33c` | `VFormatPackedWideText` | Selects a packed entry as a 16-bit format, delegates to `Text_VSNPrintfWide` and returns the destination. |
| `func_ov001_02076a54` | `DrawPackedFieldMenuEntry` | Copies the frame template to the indexed menu cell and draws the corresponding packed entry through the field text helper. |

[PACKED_RESOURCES.md](PACKED_RESOURCES.md) records the 8-byte header and 12-byte
DS view, generic borrowed payload, stride/index behavior, explicit owner-word
release, code-unit capacity, custom formatter semantics and host variadic ABI
boundary. The common owner pointer stays `void *` for the actual `void **`
release contract; a typed header is used when interpreting its data.

## Saved camera and projection

| Previous symbol | Current name | Evidence |
|---|---|---|
| `func_01ff9b70` | `BuildCameraLookAtMatrix` | Normalizes position minus target, constructs right/up with cross products, and stores the basis and negative position dot products in a 4x3 matrix. |
| `func_020289c0` | `GetOrthographicCameraBeginCallback` | Returns the address of `BeginOrthographicCamera`; it does not call it. |
| `func_02028b30` | `GetSavedCameraRestoreCallback` | Returns the address of the saved-camera restore function. |
| `func_02028c20` | `GetSavedCameraPosition` | Returns the saved position vector at backup `+0x0c`. |
| `func_02028c2c` | `GetSavedCameraTarget` | Returns the saved target vector at backup `+0x00`. |
| `func_02028c38` | `ProjectWorldPositionWithSavedCamera` | Transforms through the saved view/projection matrices, divides by W and converts to current viewport coordinates. |
| `func_ov001_02088ab0` | `ProjectWorldPositionWithSavedCameraWrapper` | Forwards the world position and both output pointers to that projector. Speech-balloon and actor-order callers supply all three arguments. |
| `ResetCameraToDefaults` | `RestoreSavedCamera` | Restores saved projection and camera vectors, then rebuilds the view matrix. It does not load fixed defaults. |
| `PXI_Init_02028dc0` | `BeginOrthographicCameraWrapper` | Calls `BeginOrthographicCamera` and forwards its result. |
| `PXI_Init_02028dcc` | `RestoreSavedCameraWrapper` | Calls the restore function and forwards its result. |


[SAVED_CAMERA.md](SAVED_CAMERA.md) records the existing 148-byte backup,
borrowed vectors, callback types, one-snapshot lifetime, view-matrix rebuild,
current viewport, fixed-point rounding and XY-only projection status.
Two native consumers and three wrappers use the common camera interface;
legacy shared caller views and descriptor erasure remain explicit port work.
The game's saved-camera projector is classified under `src/calls`, retaining
its original address and byte-exact code.

## Model animation tracks

| Previous symbol | Current name | Direct behavior and consumers |
|---|---|---|
| `func_01ffb2d4` | `GetModelAnimationTrackState` | Reads an indexed track pointer; bit 4 selects a separate pointer for index zero. `Anim_GetFrame`, the duration getter and frame setter consume its track state. |
| `func_01ffb2f8` | `SetModelAnimationFrameWithSingleWrap` | Stores a frame and subtracts one duration when it is at least that duration. Title, panel, stage-item and path-model callers use it to set animation frames. |
| `func_0202f4cc` | `GetModelAnimationDurationFx32` | Reads the bound resource's unsigned halfword frame count and shifts it left by 12. Turning animation, title animation and path-model callers use it as a duration/last-frame bound. |
| `func_ov001_02080a38` | `SetActiveModelAnimationFrames` | Visits five signed halfword track selectors at state `+0xd8`; applies the same frame only where a selector is positive. |


[MODEL_ANIMATION_TRACKS.md](MODEL_ANIMATION_TRACKS.md) records the interior
lookup origin, pointer/resource prefixes, index-zero override, null result,
fx32 duration, single-subtraction behavior and explicit caller narrowing.
Six native consumers share the recovered interface.

## Field-script delegation

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov001_02064ecc` | `ScriptCmd_LoadSceneTable` | Handler-table word 34; delegates to `LoadSceneTable` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02064edc` | `ScriptCmd_EnterMenuItem` | Handler-table word 8; delegates to `EnterMenuItem` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_020651f0` | `ScriptCmd_StartSessionScene` | Handler-table word 22; delegates to `StartSessionScene` after ByteCode_ResolveOperand; returns 0. |
| `func_ov001_02065438` | `ScriptCmd_ShowSessionNameEntry` | Handler-table word 44; delegates to `ShowSessionNameEntry` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_020655e8` | `ScriptCmd_HandleFieldPanelCommand` | Handler-table word 74; delegates to `HandleFieldPanelCommand` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065638` | `ScriptCmd_LoadCameraParams` | Handler-table word 80; delegates to `LoadCameraParams` after ByteCode_ResolveOperand; returns 1. |
| `func_ov001_02065680` | `ScriptCmd_OpenFieldMenuMode` | Handler-table word 84; delegates to `OpenFieldMenuMode` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065690` | `ScriptCmd_SetSceneLock` | Handler-table word 86; delegates to `SetSceneLock` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_020656c4` | `ScriptCmd_ClearSceneEntry` | Handler-table word 90; delegates to `ClearSceneEntry` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_0206576c` | `ScriptCmd_ResetStageOriginIfActive` | Handler-table word 96; delegates to `ResetStageOriginIfActive` after no local decoding; returns 1. |
| `func_ov001_020658b8` | `ScriptCmd_ResetOverlaySelection` | Handler-table word 106; delegates to `ResetOverlaySelection` after no local decoding; returns 1. |
| `func_ov001_02065910` | `ScriptCmd_LoadCenteredScreenSprite` | Handler-table word 110; delegates to `LoadCenteredScreenSprite` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065950` | `ScriptCmd_AdvanceRecordStep` | Handler-table word 114; delegates to `AdvanceRecordStep` after no local decoding; returns 1. |
| `func_ov001_020659b4` | `ScriptCmd_AddStageSlotLock1` | Handler-table word 120; delegates to `StageEvent_SetHoldBit1` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_020659c8` | `ScriptCmd_TryActivateStageSlot` | Handler-table word 122; delegates to `TryActivateStageSlot` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065a28` | `ScriptCmd_SaveCurrentSpawnPoint` | Handler-table word 132; delegates to `SaveCurrentSpawnPoint` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065a54` | `ScriptCmd_SetMenuHighlight` | Handler-table word 136; delegates to `SetMenuHighlight` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065c10` | `ScriptCmd_BindScriptHandlersSlot7` | Handler-table word 148; delegates to `BindScriptHandlersSlot7` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065c4c` | `ScriptCmd_AllocSessionNameTable` | Handler-table word 152; delegates to `AllocSessionNameTable` after ScriptVm_ReadOperandInt; returns 1. |
| `func_ov001_02065dbc` | `ScriptCmd_CommitChapterClearRecords` | Handler-table word 50; delegates to `CommitChapterClearRecords` after no local decoding; returns 1. |
| `func_ov001_02065f20` | `ScriptCmd_ClearFieldCounters` | Handler-table word 178; delegates to `ClearFieldCounters` after no local decoding; returns 1. |
| `func_ov001_02065f80` | `ScriptCmd_ResetGaugeDisplay` | Handler-table word 186; delegates to `ResetGaugeDisplay` after no local decoding; returns 1. |

[FIELD_SCRIPT_DELEGATES.md](FIELD_SCRIPT_DELEGATES.md) records the real callee
behavior, pointer/integer decoding, u16 narrowing, constant returns and native
dispatcher typing limits. The StartSessionScene command keeps its distinct
zero return; names do not imply a shared success/advance protocol.

## Explicitly unresolved

The vector view at `data_027e0160` overlaps `data_027e0164`, used by the older
object-hit view. This block does not assign two independent typed objects to
that storage or infer a full allocation from one call's accesses. It needs a
separate check of lifetimes, ownership and callers before a shared union or
more specific names can be justified.
