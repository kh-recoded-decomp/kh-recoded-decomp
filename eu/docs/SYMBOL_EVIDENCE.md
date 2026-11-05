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

## Late-menu rendering and resources

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov075_020cd0c0` | `BuildItemPickerListForType` | Builds cached item/record pointer list according to enabled type bit, type11=all, nonzero count and sortKey<9999; excludes item indices0..127; qsort uses item-picker comparator. |
| `func_ov085_020c1cdc` | `BuildShopItemListForType` | Same list filter as ov075; uses shop count builder and comparator. No type/index validation. |
| `func_ov075_020cd470` | `LoadItemPickerTextureDrawParams` | Loads encoded archive/index file; dispatches resource; selects texture/palette entry0; extracts width/height/imageParam/paletteBase and frees source. Assumes valid entries; handles compressed4x4 key/palette units. |
| `func_ov076_020c96b8` | `LoadSlotMenuTextureDrawParams` | Same entry0 extraction as ov075 with slot-menu overlay binding. Keep independent function. |
| `func_ov077_020c66ec` | `LoadItemScreenTextureDrawParams` | Same entry0 extraction as ov075 with item-screen overlay binding. Keep independent function. |
| `func_ov075_020cd874` | `DrawItemPickerTexturedQuad` | Builds ImageQuad scale/translation, rotation/texture/palette/color and four UV/vertex pairs. BOOL controls decal polygon mode; y<=0 adds1fx32 height; no clipping/state restoration. |
| `func_ov077_020c9f80` | `DrawItemScreenImageFromPackedArgs` | select high16=image index/low16=color; pos high/low signed16=XY; depth passed separately. Emits full textured quad, unlike ov075 subrectangle/decal interface. |
| `func_ov075_020ceea4` | `UpdateItemPickerCharUpload` | Skips paused work/mismatched VBlank parity; if upload enabled copies2400h bytes to BG1 char+140h; updates renderer only if renderer busy==0. Busy does not guard upload. |
| `func_ov076_020cacb4` | `UpdateSlotMenuCharUpload` | Same parity/upload/idle-renderer behavior with gSlotMenuPanelWork, distinct from item-picker work. |
| `func_ov075_020cef00` | `BuildItemPickerFrameTilemap` | Builds 3x3-style frame in32x24 screen, fills middle strips and clears outside. Upper-clamps only, narrows origins/sizes unsigned, preserves width-2 behavior. |
| `func_ov076_020cad10` | `BuildSlotMenuFrameTilemap` | Same32x24 frame builder using distinct slot-menu tile table. No lower rectangle validation. |
| `func_ov075_020cf204` | `HandleItemPickerTextTag` | Tags1/2/4 assignF2/highlight/FA;1F centers next line using measured width and linefeed+vSpace. Other tags untouched; retain(width+1)/2 arithmetic. |
| `func_ov076_020cb154` | `HandleSlotMenuTextTag` | Same tag contract; distinct work and helper binding TextCanvas_GetLineWidth rather than MeasureTextLine. |
| `func_ov075_020d0f70` | `LoadItemPickerMenuTipImages` | Opens literal ui/menu/tips.p2 and language tips archive; loads85h entries with sequential localized fallback only for empty primary entry, extracts texture/palette metadata, frees buffers/containers, toggles dispatch0 then1. |
| `func_ov076_020ccda4` | `LoadSlotMenuTipImages` | Same85h tip metadata/fallback algorithm with slot menu path globals. Fallback counter advances only for empty primary; VRAM metadata survives source free. |
| `func_ov077_020c9df0` | `LoadItemScreenMenuTipImages` | Same85h tip metadata/fallback algorithm with item-screen path globals; preserve independent overlay binding. |
| `func_ov085_020c1fd4` | `LoadShopMenuTipImages` | Same85h tip metadata/fallback algorithm with shop path globals; preserve independent overlay binding. |
| `func_ov091_020bf1b4` | `LoadReportTopMessageContainers` | Opens all3 gReportTopResourcePaths with modeE/head allocation into owner table work+4; no prior-owner cleanup/failure check. |
| `func_ov097_020bf6c8` | `LoadStoryReportMessageContainers` | Opens all3 gStoryReportResourcePaths with modeE/head allocation into work+18h. Existing private type Ov101State is misleading; no prior-owner cleanup. |
| `func_ov103_020bef14` | `LoadTheaterReportMessageContainers` | Opens both gTheaterReportResourcePaths modeE/head into work+10h;2entries rather than3; no prior-owner cleanup. |
| `func_ov095_020c0064` | `DrawItemGridTextWithShadow` | DrawTextColored at XY+1 with color+1 for both colors then foreground suppliedXY/colors. Legacy flags parameter is second color here, not proven flags. |
| `func_ov099_020c060c` | `DrawEnemyViewerTextWithShadow` | Same two-pass shadow operation as ov095; preserve integer color+1 and custom tagged-text semantics. |
| `func_ov099_020becb4` | `InitEnemyViewerScreen` | Sets global work, clearsD6F8h bytes, initializes progress/resources/scroll/text/slots/model viewer and enters mode1. Returns1; not complete allocation-schema proof. |
| `func_ov099_020bedd0` | `DestroyEnemyViewerScreen` | Destroys viewer/models/object managers, frees resources, resets base rotation/dirty state, releases slots4/0 and manager, frees message container and clears global. Preserve cleanup order; not full renderer restore. |
| `func_ov099_020c2078` | `LoadEnemyViewerSelectionModels` | Releases old selection models; clears/builds each104h model from selection list; selects all5tracks, attaches models and applies pose. No selection/capacity guard. |
| `func_ov103_020c033c` | `InitTheaterReportScreen` | ClearsCBC4h work; clamps negative restored selection to0; loads messages/graphics/background/text/slots, setups list/unlocks, redraws and sets phase2. No upper selection guard. |
| `func_ov103_020bf5e8` | `CreateTheaterReportSlotEntries` | Initializes manager at work+174h from container entryDh, creates12 slots with14h descriptor stride. No complete descriptor schema inferred. |
| `func_ov086_020bfba0` | `RefreshRecordStatisticsRows` | Clears text via virtualslot1; dirties layer18h/trackerrow19h; draws statistic rows0..3 using established RecordPageMenu. |
| `func_ov086_020bf3b4` | `CountSetRecordGroupFlags` | Sums earlier group counts for base, scans group and counts IsSessionFlagSet(base+i+581h). No group bounds validation or further flag-role claim. |
| `func_ov088_020bed2c` | `InitOverlay088CaptionLayer` | Loads literal ui/menu/str/&/cd.s.z into packed view+34h; inits text layer, draws entry0 at(4,0), uploads and dirties1Ah. Does not expand unknown cd abbreviation. |
| `func_ov088_020bedf0` | `DestroyOverlay088CaptionLayer` | FreePointerIfSet at owner slot context+34h, then DestroyFndObjectList. Normalize actual void** release if changing types; cached view fields become stale. |
| `func_ov097_020c1864` | `InitStoryReportSpriteFromFile` | Clears2Ch prefix; loads resource at+28h with flags11h; RebindSpriteToCell(slot,1,1,0); true return. No load failure guard. |
| `func_ov097_020c188c` | `ReleaseStoryReportSpriteResource` | Frees/clears+28h owner if nonzero; clears upper3bits at byte+26h; returns1. Does not clear whole sprite or other flags. |
| `func_ov079_020c4c0c` | `SaveOptionsAndCloseConfigMenu` | Plays close sound; ConfigMenu_SaveOptions(work); PopStackEntry; StartSubScene(0,-1,0). Preserve persistence/navigation order. |
| `func_ov087_020c4734` | `DrawChoiceWindowTextAndUpload` | Uses indexed34h layer at work+9F8h; draws text at(40h,2) with411h flags and uploads. No window bounds guard; flags remain numeric. |

[UI_RENDER_HELPERS.md](UI_RENDER_HELPERS.md) records per-overlay bindings,
metadata/lifetime contracts, packed coordinates, bounds, tag behavior, upload
scheduling and paired cleanup. Shadow-text parameters keep their two-color
meaning; local view names do not claim complete allocation layouts.

## Calendar conversion helpers

| Previous symbol | Current name | Established operation |
|---|---|---|
| `func_02022570` | `ParseDecimalLong` | Calls `strtol(text, NULL, 10)` and forwards its result. |
| `func_02022584` | `IsLeapYearSince1900` | Tests the Gregorian leap condition on `tm_year`, not on a full civil year. |
| `func_02022688` | `NormalizeCalendarFieldWithCarry` | Writes a floor-division remainder back to one field and checked-adds the quotient to its next larger field. |
| `func_020229dc` | `NormalizeCalendarToTime` | Converts a local calendar copy, copies normalization back only on success and returns the 32-bit time word or -1. |


[CALENDAR_HELPERS.md](CALENDAR_HELPERS.md) records the year-since-1900 origin,
checked floor carry, copy-on-success behavior, 36-byte storage and reserved
ninth word. The helpers expose their actual pointer inputs and logical argument
counts; native time and long widths remain explicit port constraints.

## UI progress and slot/state contracts

| Previous name | Current name | Evidence |
|---|---|---|
| `func_ov077_020c7ce8` | `UpdateItemScreenCharUpload` | Same paused/parity-gated2400h copy to BG1char+140h and idle-renderer update as075/076, using gItemListPanelWork. |
| `func_ov077_020c7d44` | `BuildItemScreenFrameTilemap` | Same32x24 three-style frame-tilemap algorithm as075/076 with item-screen frame table. |
| `func_ov077_020c8188` | `HandleItemScreenTextTag` | Same colorsF2/highlight/FA and1F centered-next-line tag callback, using MeasureTextLine_020c8120 and item-screen owner. |
| `func_ov095_020c0148` | `CreateItemGridSlots` | Builds manager at180h from container entry31h and creates13 grid slots using gItemGridLayoutRecords with14h stride. |
| `func_ov091_020bf7a8` | `CreateReportTopPanelSlots` | Initializes managerF4h from entry7, binds extra resource, creates6slots with18h descriptor stride; initializes second manager6528h from entry4 and creates one slot. |
| `func_ov095_020c1628` | `UpdateItemGridBackgroundVariant` | Changes BG3screen to resource154h when selected variant1 and stored variant1, marks stored2; otherwise restores resource144h when stored2, marks1. |
| `func_ov091_020c12d4` | `UpdateReportTopFlagProgress` | Counts8table-selected global flags, sets11B2h+i for found entries, marksnew entry category(2,2) when unacknowledged, stores percentageC9FCh. |
| `func_ov091_020c1370` | `UpdateReportTopCounterProgress` | Counts40nonzero17-bit counters selected by table, sets1172h+i, marks new-entry category(2,3) when unacknowledged, stores percentCA00h. |
| `func_ov076_020c8b48` | `IsSlotMenuTotalWithinLimit` | Sums eight unsigned-halfword values at49818h and returns total<=100. |
| `func_ov076_020ca644` | `ApplySlotMenuItemReward` | Called by ItemList_ReturnCursorItem with selected definition reward. Dispatches B7h..BDh into counters, level-threshold helper, resets and feedback requests. |
| `func_ov077_020c7678` | `ApplyItemScreenItemReward` | Equivalent selected-item reward dispatch B7h..BDh, using item-screen helper bindings and QueueAndPlaySound feedback. |
| `func_ov075_020cecf0` | `AreItemPickerSessionStatesZero` | Returns true only when every session state word selected by global byte count is zero; zero count is true. |
| `func_ov076_020cab00` | `AreSlotMenuSessionStatesZero` | Same zero-state scan for slot-menu copy; global array begins session+27A8h. |
| `func_ov077_020c7b34` | `AreItemScreenSessionStatesZero` | Same zero-state scan for item-screen copy. |
| `func_ov091_020c1774` | `GetReportTopMode` | ReturnsCC68h word; paired SetSceneMode writes same field and UpdateRecordMenuScene dispatches by getter. |
| `CountUnlockedRecordGroupEntries` | `CountSetRecordGroupFlags` | Counts set flags at0x581+group base+index; no unlocked/completed meaning assigned. |

[UI_PROGRESS_SLOTS.md](UI_PROGRESS_SLOTS.md) records fixed slot counts/strides,
report flags and counters, native reward dispatch, zero-state scans and the
report mode word. The previous unlocked wording for the record-group counter
is corrected to a set-flag operation; gameplay meaning remains unproven.

## Explicitly unresolved

The vector view at `data_027e0160` overlaps `data_027e0164`, used by the older
object-hit view. This block does not assign two independent typed objects to
that storage or infer a full allocation from one call's accesses. It needs a
separate check of lifetimes, ownership and callers before a shared union or
more specific names can be justified.

## Session state reset and menu delegates

`ClearFieldCounters` is corrected to `ClearSessionStateWords`: only three zero
stores at session +0x27a8/+0x27ac/+0x27b0 are proved. The corresponding script
command and three UI tail-call thunks use that neutral wording.
[SESSION_STATE_WORDS.md](SESSION_STATE_WORDS.md) records the addresses, literal
Thumb targets, consumers, partial native view and unresolved return declarations.
No counter, ready or idle meaning is assigned to these state values.

## Camera helper contracts

Twenty helpers now describe overlay042 collision registration/frustum state,
manager and controller views, follow-point operations, ordered updates and HUD
delegates. [CAMERA_HELPER_CONTRACTS.md](CAMERA_HELPER_CONTRACTS.md) records the
old/current names, native offsets, borrowed lifetimes and real return evidence.
Getter types expose proved pointers and the consumed magnitude result; the
remaining opaque controller layouts and legacy shared adapters are explicit.

## Geometry DMA and overlay barriers

Seven rendering helpers now describe their actual geometry command/DMA roles,
including the misleading previous names `FSi_WaitForCardThread` and
`InitializeArchiveBackend`. [GEOMETRY_TRANSFERS.md](GEOMETRY_TRANSFERS.md) records
the busy word, callback, full buffer extent, fast-mode selector, overlay barriers
and legacy DS adapters. The eight-word BSS allocation is preserved; its first
word is a DMA selector rather than an RNG seed.

## Joint, SBC and texture identity helpers

Five helpers use the established joint-result and SBC-state types and names
from their GX operations. [JOINT_TEXTURE_HELPERS.md](JOINT_TEXTURE_HELPERS.md)
records identity flags, exact command payloads, unconditional cursor advance,
untouched fields and the two-argument texture hook contract. Separate texture
entrypoints remain separate; neither helper initializes an entire matrix.

## Task, input and VM resource helpers

Twenty-two operations now name their actual task, mutex, input, wireless, script
buffer and archive roles. [TASK_INPUT_VM_HELPERS.md](TASK_INPUT_VM_HELPERS.md)
records the 44-byte task/native manager view, borrowed work lookup, collection
lifetime, real delegate/WM returns, sampling units and buffer ownership limits.
The former root-heap lookup is the running task's work getter.

## Vector callbacks and collision helper lifetimes

Seventeen operations now describe quaternion rotation, per-component callbacks,
segment/cylinder queries, collision-vector adapters and guarded resource release.
[VECTOR_COLLISION_HELPERS.md](VECTOR_COLLISION_HELPERS.md) records the real
quaternion/input order, callback sequencing, query radius and borrowed result,
flag guards and ownership limits. No collision algorithm is rewritten.

## Timing, loading, audio and random services

Twenty-three helpers now name their actual tween, loader, sound-command, indexed
animation, brightness, platform-clock and RNG operations.
[ENGINE_SERVICE_HELPERS.md](ENGINE_SERVICE_HELPERS.md) records evidence for each
entrypoint, the actual tween argument order, clock/flag units, queue ownership
limits and exact three-word RNG arithmetic without merging split DATA owners.

## Overlay-qualified entry identities

`InstallSessionOv036Handlers` and `IsShapeWithinActiveCameraView` now bind to
their proved ov036/ov043 targets rather than unrelated ov035 DATA and ov039
input code at equal RAM addresses. [OVERLAY_IDENTITY_BINDINGS.md](OVERLAY_IDENTITY_BINDINGS.md)
records state/mode loading evidence, exact relocation-owner narrowing, preserved
entry bytes and the remaining native callback/visibility boundaries.

## Session handlers and packed placement

Fourteen additional helpers now name overlay-specific session installers,
state/archive queries, a raw flag-mask query, saved placement and the native
callback/address adapter. [SESSION_HANDLERS_PLACEMENT.md](SESSION_HANDLERS_PLACEMENT.md)
records the twelve heterogeneous callback slots and null rules, bank lifetimes,
packed-bit widths/order and unresolved host address protocol. The placement
definitions use actual vector/angle storage without pointer truncation.

## Font resources and width fallback

Three helpers now use explicit font-resource, text-layer, text and fallback
inputs. [FONT_RESOURCE_FALLBACK.md](FONT_RESOURCE_FALLBACK.md) records the native
12-byte resource ownership, cached-default restoration, strict width threshold,
flags versus alternate color, UTF16 controls and actual two-input loader chain.
The partial layer view does not define a complete host allocation.

## MAIN resource lifetime and service helpers

Twenty-two helpers now describe the actual heap-resize/texture-trim chain,
panel copies/submission, record initialization, material scaling, guarded slot
cleanup, linked-list adapters, movement/spatial update and selection refresh.
[MODEL_RESOURCE_OWNERSHIP.md](MODEL_RESOURCE_OWNERSHIP.md) and
[MAIN_RESOURCE_SERVICE_HELPERS.md](MAIN_RESOURCE_SERVICE_HELPERS.md) record
logical inputs, actual-size returns, upload/CPU-buffer lifetimes and native ABI
limits. The old free/sound labels do not describe those heap operations.

## Field/panel script skip and sound contracts

Thirty-four helpers now name their real VM skip, BGM-cache, sound/stream command
and resource-binding roles. [SCRIPT_SKIP_SOUND_CONTRACTS.md](SCRIPT_SKIP_SOUND_CONTRACTS.md)
records exact VM owners, distinct request/advance branches, command/resume
results, live-register boundaries and queue/load limits. FinishSkip's former
busy guard is identified as the separate handler-table word at index 3; its
native view preserves the DATA owners and instructions.

## Actor movement, effect and callback owners

Thirty-four operations now describe actor/enemy movement, event/AI dispatch,
animation bookkeeping, entry requests, generic lists, contact callbacks and
scene-task deactivation. [ACTOR_OPERATION_CONTRACTS.md](ACTOR_OPERATION_CONTRACTS.md)
records separate owners and concrete fields, callback arguments/results,
borrowed velocity, radial effect geometry and unresolved gameplay labels.
The overlay052 velocity getter is distinct from overlay017's existing API.

## Subtitle, scroll and board-widget contracts

Nineteen helpers now describe movie-script waits/stream requests, subtitle
control and glyph rendering, scroll blend adapters, text-layer setup and
board-widget blit/clear/deferred cleanup.
[SUBTITLE_SCROLL_WIDGET_CONTRACTS.md](SUBTITLE_SCROLL_WIDGET_CONTRACTS.md)
records byte-string decoding, cursor/alignment distinctions, captured draw
coordinates, MMIO effects, borrowed buffers and native return boundaries.

## Field-script resource, object and actor commands

Thirty-one entrypoints now name the demonstrated field resource/menu/session
adapters, two distinct object managers and actor camera/probe/record commands.
[FIELD_SCRIPT_EXTENSIONS.md](FIELD_SCRIPT_EXTENSIONS.md) records the shared
MAIN interpreter, group/entry pairs, run/resume control, copied versus borrowed
inputs, persistent record writes and remaining semantic limits. The session
callback documentation now gives the verified absent/zero/nonzero behavior.

## Field HUD, menu and message-window ownership

Twenty-eight helpers now name HUD graphics/font/task operations, menu entry
queries, message-window resource callbacks and subscene overlay loading.
[FIELD_HUD_MESSAGE_HELPERS.md](FIELD_HUD_MESSAGE_HELPERS.md) records separate
work owners, exact teardown and upload order, numeric ID narrowing, queue
callbacks, asynchronous load limits and per-call fade behavior. Existing script
and loader-queue references use the accepted EU names.

## Menu descriptors, popup tasks and registered empty hooks

Eighty entrypoints now name confirmation/selection operations, popup task/window
helpers, overlay-qualified lifecycle callbacks and registered empty hooks.
[MENU_CALLBACKS_AND_POPUP_CONTRACTS.md](MENU_CALLBACKS_AND_POPUP_CONTRACTS.md)
records descriptor layout differences, callback-presence input consumption,
consumed versus residual returns, task/work/window ownership, text-copy lifetime,
HP predicates and unresolved state/category meanings. The native empty handlers
and their distinct descriptor registrations remain intact.

## Title-session, profile-panel and player-card helpers

Fifty-eight entrypoints now name title-session/display adapters, profile-panel
text/graphics ownership, native save-record operations and player-card list
behavior. [TITLE_PROFILE_CARD_CONTRACTS.md](TITLE_PROFILE_CARD_CONTRACTS.md)
records distinct work owners, borrowed buffers, low-bit rather than boolean
flags, pointer versus status returns, source-to-VRAM uploads, numeric page
transitions and signed cursor boundaries. Unsupported CARD/day/tint comments
are replaced with the observed operations.
