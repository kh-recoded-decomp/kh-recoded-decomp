# Area events, transitions and reward resources

This document records 17 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The area scene's state handlers return signed -1 to hold and nonnegative next states to advance. Waiters test the exact panel/screen predicate documented below. They do not unload overlays or free child work themselves. The screen-mode input is the owner's signed mode byte, not position; the screen helper's +8/+0x0c values are brightness caches in fixed point with 12 fractional bits.

Collision control formats the numbered `bugcol` name and applies mesh enable to matching face kinds 1, 2 and 4. Levels 2/3 enable while 0/1 disable: true clears face flag 0x4000, false sets it, and both increment the collision-change counter. The fixed 16-byte formatting buffer and original unchecked indices remain part of the matched behavior.

Area refresh coordinates event groups, visible objects and layers through the actual global owner. Only progress recalculation consumes the wrapper's area argument. The object-exclusion predicate rejects already-active stage objects or info kind 0x37; it assigns no gameplay name to that numeric kind. Slot configuration applies two established entry flag setters with their different polarities, then resets slots; it uses the selected slot ID as a bound, not a generic count.

The transition/audio state sets its explicit counter to 15 and preserves numeric session flag 0x3308 and sound operations. The numeric field request (-3,3) retains its unproven meaning. The exit waiter writes child state 2 after its screen/panel guards, without destroying that child. The old Movie context label is retained only as a source symbol, not as proof of video decoding.

The reward model belongs to the exact data_ov040_020be280 work/model global and uses a temporary camera/projection with top/bottom +/-0x2400 and left/right +/-0x3000. Its draw callee restores the global camera/projection state. It does not draw arbitrary actor models.

A separate shared reward allocation contains 20 bytes: two record-handle words for archive 4 files 0/14, a palette entry, a pending-item word at +0x0c and timer at +0x10. Construction initializes the resource prefix and clears the pending item, but does not initialize the fifth-word timer. The aliasing between resources and reward-popup state is proven by identical global ownership and consumers, not offset analogy.

The animation-table getter follows recordHandle[index].state +8 and returns borrowed table storage; the mode-6 actor path proves indices 0/1. Index 2 is a different palette-entry type, so an arbitrary-index array contract would be wrong. Reward codes 0x1e0..0x1ed map to stack item IDs 0xcb..0xd8; unsupported codes return the all-ones -1 sentinel. These IDs are consumed as StackSlot IDs rather than session flag indices.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov040:020bc774` | THUMB | `func_ov040_020bc774` | `SetAreaBugCollisionEnabledByLevel` | [eu/src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c](../src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c) |
| `ov040:020bc83c` | THUMB | `func_ov040_020bc83c` | `RefreshAreaEventObjectAndLayerState` | [eu/src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c](../src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c) |
| `ov040:020bcc44` | THUMB | `func_ov040_020bcc44` | `IsStageObjectExcludedFromAreaGroups` | [eu/src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c](../src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c) |
| `ov040:020bcd28` | THUMB | `func_ov040_020bcd28` | `ConfigureAreaSceneSlotsAndReset` | [eu/src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c](../src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c) |
| `ov040:020bd0f4` | THUMB | `func_ov040_020bd0f4` | `AreaSceneState_WaitForPanelReady` | [eu/src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c](../src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c) |
| `ov040:020bd418` | THUMB | `func_ov040_020bd418` | `AreaSceneState_SetTransitionAudioAndFlags` | [eu/src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c](../src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c) |
| `ov040:020bd548` | THUMB | `func_ov040_020bd548` | `AreaSceneState_BeginScreenTransition` | [eu/src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c](../src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c) |
| `ov040:020bd5e0` | THUMB | `func_ov040_020bd5e0` | `AreaSceneState_RestoreFieldWhenScreenIdle` | [eu/src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c](../src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c) |
| `ov040:020bd604` | THUMB | `func_ov040_020bd604` | `AreaSceneState_StartIdleObjects` | [eu/src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c](../src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c) |
| `ov040:020bd624` | THUMB | `func_ov040_020bd624` | `AreaSceneState_BeginFadeOut` | [eu/src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c](../src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c) |
| `ov040:020bd648` | THUMB | `func_ov040_020bd648` | `AreaSceneState_WaitForExitTransition` | [eu/src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c](../src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c) |
| `ov040:020bd748` | THUMB | `func_ov040_020bd748` | `AreaSceneState_Hold` | [eu/src/overlays/ov040/auto/AreaSceneState_Hold.c](../src/overlays/ov040/auto/AreaSceneState_Hold.c) |
| `ov040:020bdb70` | THUMB | `func_ov040_020bdb70` | `DrawAreaRewardModel` | [eu/src/overlays/ov040/calls/DrawAreaRewardModel.c](../src/overlays/ov040/calls/DrawAreaRewardModel.c) |
| `ov040:020bdba4` | THUMB | `func_ov040_020bdba4` | `StartAreaEventsAdapter` | [eu/src/overlays/ov040/calls/StartAreaEventsAdapter.c](../src/overlays/ov040/calls/StartAreaEventsAdapter.c) |
| `ov040:020bdc44` | THUMB | `func_ov040_020bdc44` | `RewardCodeToStackItemId` | [eu/src/overlays/ov040/calls/RewardCodeToStackItemId.c](../src/overlays/ov040/calls/RewardCodeToStackItemId.c) |
| `ov040:020bdf9c` | THUMB | `func_ov040_020bdf9c` | `InitAreaRewardResources` | [eu/src/overlays/ov040/calls/InitAreaRewardResources.c](../src/overlays/ov040/calls/InitAreaRewardResources.c) |
| `ov040:020be028` | THUMB | `func_ov040_020be028` | `GetAreaRewardAnimationTable` | [eu/src/overlays/ov040/calls/GetAreaRewardAnimationTable.c](../src/overlays/ov040/calls/GetAreaRewardAnimationTable.c) |

## SetAreaBugCollisionEnabledByLevel

Identity: `ov040:020bc774`, THUMB, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov040_020bc774`.

EU entrypoint: [eu/src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c](../src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c).

```c
void SetAreaBugCollisionEnabledByLevel(u32 firstArg, int count, u32 unusedArg, u32 secondArg);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Formats the numbered bugcol name and applies collision enable=(level>1) to all matching faces. Source: [eu/src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c:1-18](../src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c).
- The caller supplies areaIndex and the computed progress level0..3. Source: [src/ov040/unclassified_helpers/UpdateAreaProgressLevel_020bc784.c:1-64](../../src/ov040/unclassified_helpers/UpdateAreaProgressLevel_020bc784.c).
- Searches named points and applies SetMeshEnabled across associated face kinds1,2,4. Source: [src/ov001/overlay_handling/ApplyToNamedCollisionFaces_020680fc.c:1-38](../../src/ov001/overlay_handling/ApplyToNamedCollisionFaces_020680fc.c).
- True clears face flag0x4000; false sets it and both increment the collision-change counter. Source: [src/ov001/unclassified_helpers/SetMeshEnabled_02068180.c:1-18](../../src/ov001/unclassified_helpers/SetMeshEnabled_02068180.c).

Contract limits:

- Formats into a fixed16-byte local buffer as the original does.
- Levels2/3 enable collision; levels0/1 disable it.

## RefreshAreaEventObjectAndLayerState

Identity: `ov040:020bc83c`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov040_020bc83c`.

EU entrypoint: [eu/src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c](../src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c).

```c
void RefreshAreaEventObjectAndLayerState(u32 handle);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Refreshes area event state, switches visible objects, recalculates progress for the supplied area and switches layers. Source: [eu/src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c:1-14](../src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c).
- Releases/holds event groups and counts pending events based on exact current/previous areas. Source: [src/ov040/unclassified_helpers/RefreshAreaEvents_020bc5b8.c:1-63](../../src/ov040/unclassified_helpers/RefreshAreaEvents_020bc5b8.c).
- Changes object visibility only when current area differs from previous. Source: [src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c:1-78](../../src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c).
- Enables the current area layer group and disables the previous one. Source: [src/ov040/unclassified_helpers/SwitchAreaLayers_020bc710.c:1-41](../../src/ov040/unclassified_helpers/SwitchAreaLayers_020bc710.c).

Contract limits:

- Only progress recalculation consumes the wrapper argument; other callees obtain their exact shared owner globally.

## IsStageObjectExcludedFromAreaGroups

Identity: `ov040:020bcc44`, THUMB, native extent 58 bytes (including any configured pool). Previous symbol: `func_ov040_020bcc44`.

EU entrypoint: [eu/src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c](../src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c).

```c
BOOL IsStageObjectExcludedFromAreaGroups(int itemIndex);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns true if stage object is already active or its referenced info kind is0x37. Source: [eu/src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c:1-38](../src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c).
- The only source caller found excludes true results before grouping objects spatially. Source: [src/ov040/shared_engine/SortObjectsIntoAreaGroups_020bc970.c:1-82](../../src/ov040/shared_engine/SortObjectsIntoAreaGroups_020bc970.c).

Contract limits:

- No name is invented for info kind0x37.
- No index bounds or null checks exist.

## ConfigureAreaSceneSlotsAndReset

Identity: `ov040:020bcd28`, THUMB, native extent 66 bytes (including any configured pool). Previous symbol: `func_ov040_020bcd28`.

EU entrypoint: [eu/src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c](../src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c).

```c
unsigned int ConfigureAreaSceneSlotsAndReset(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- For slots before the last selected slot, applies both existing entry flag setters with1; applies0 to the last slot when positive, resets scene slots and returns state2. Source: [eu/src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c:1-30](../src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c).
- The first setter controls entry+0x104 bit0. Source: [eu/src/overlays/ov001/calls/SetSceneSlotDrawingEnabled.c:1-15](../src/overlays/ov001/calls/SetSceneSlotDrawingEnabled.c).
- The second setter uses inverse polarity for entry+0x104 bit3. Source: [eu/src/overlays/ov001/calls/func_ov001_02067d0c.c:1-15](../src/overlays/ov001/calls/func_ov001_02067d0c.c).

Contract limits:

- The selected slot ID supplies the bound; no generic object count is inferred.
- When lastSlot<=0 no flag setter is called.

## AreaSceneState_WaitForPanelReady

Identity: `ov040:020bd0f4`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov040_020bd0f4`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c](../src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c).

```c
u32 AreaSceneState_WaitForPanelReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Polls the field panel readiness adapter; on success clears initialization flag1, clears current task signal and returns state5. Source: [eu/src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c:1-20](../src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c).
- Returns ready immediately outside panel mode4; otherwise requests panel style2 with mode-sensitive flag. Source: [eu/src/overlays/ov001/calls/RequestSubsceneMode0Or1FromMode4.c:1-16](../src/overlays/ov001/calls/RequestSubsceneMode0Or1FromMode4.c).

Contract limits:

- Returns -1 while the panel request remains unready.

## AreaSceneState_SetTransitionAudioAndFlags

Identity: `ov040:020bd418`, THUMB, native extent 108 bytes (including any configured pool). Previous symbol: `func_ov040_020bd418`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c](../src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c).

```c
u32 AreaSceneState_SetTransitionAudioAndFlags(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Sets counter+0x84 to15, queues a sound, conditionally restores field BGM, sets the owner transition flags and model flag0x8000, then returns state9. Source: [eu/src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c:1-25](../src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c).

Contract limits:

- The exact human-facing role of the transition and session flag0x3308 remains unspecified.
- Uses the exact shared gMovieContextState owner referenced by overlay040, not an arbitrary movie object.

## AreaSceneState_BeginScreenTransition

Identity: `ov040:020bd548`, THUMB, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov040_020bd548`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c](../src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c).

```c
u32 AreaSceneState_BeginScreenTransition(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Passes owner mode byte+0x1c to the field screen transition initializer, marks flag0x20 and returns state11. Source: [eu/src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c:1-14](../src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c).
- Sets screen mode and caches main/sub brightness as12-fraction-bit values before scheduling brightness restoration. Source: [eu/src/overlays/ov001/calls/BeginFieldScreenModeTransition.c:1-51](../src/overlays/ov001/calls/BeginFieldScreenModeTransition.c).

Contract limits:

- The mode byte is signed on input.
- Do not interpret screen+8/+0xc as positions; they cache brightness.

## AreaSceneState_RestoreFieldWhenScreenIdle

Identity: `ov040:020bd5e0`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov040_020bd5e0`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c](../src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c).

```c
u32 AreaSceneState_RestoreFieldWhenScreenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen mode idle, then requests field values(-3,3), marks the negative field value and returns state5. Source: [eu/src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c:1-18](../src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c).

Contract limits:

- The meaning of the numeric field request remains opaque.

## AreaSceneState_StartIdleObjects

Identity: `ov040:020bd604`, THUMB, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov040_020bd604`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c](../src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c).

```c
u32 AreaSceneState_StartIdleObjects(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Starts idle scene objects, enables the field callback path, marks flag0x20 and returns state15. Source: [eu/src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c:1-13](../src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c).

Contract limits:

- The actual callbacks remain responsible for object allocation/activation.

## AreaSceneState_BeginFadeOut

Identity: `ov040:020bd624`, THUMB, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov040_020bd624`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c](../src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c).

```c
u32 AreaSceneState_BeginFadeOut(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle, starts fade-out with the signed owner mode and returns state16. Source: [eu/src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c:1-17](../src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c).

Contract limits:

- Returns -1 without starting fade while screen is busy.

## AreaSceneState_WaitForExitTransition

Identity: `ov040:020bd648`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov040_020bd648`.

EU entrypoint: [eu/src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c](../src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c).

```c
u32 AreaSceneState_WaitForExitTransition(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle and, unless owner flag0x10 bypasses it, a successful Panel_TryBeginTransition4; then writes child scene state2 and returns state17. Source: [eu/src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c:1-22](../src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c).

Contract limits:

- Does not unload the overlay or free the child work.

## AreaSceneState_Hold

Identity: `ov040:020bd748`, THUMB, native extent 6 bytes (including any configured pool). Previous symbol: `func_ov040_020bd748`.

EU entrypoint: [eu/src/overlays/ov040/auto/AreaSceneState_Hold.c](../src/overlays/ov040/auto/AreaSceneState_Hold.c).

```c
int AreaSceneState_Hold(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns -1 without side effects. Source: [src/ov040/library_nns_gfd/Gfd_DefaultFreeTexVram_020bd728.c:1-1](../../src/ov040/library_nns_gfd/Gfd_DefaultFreeTexVram_020bd728.c).
- The area state dispatcher treats a negative state result as holding the current state. Source: [eu/src/overlays/ov040/calls/RunMenuStateMachine.c:1-4](../src/overlays/ov040/calls/RunMenuStateMachine.c).

Contract limits:

- Not a VRAM allocator despite the shared source label.

## DrawAreaRewardModel

Identity: `ov040:020bdb70`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov040_020bdb70`.

EU entrypoint: [eu/src/overlays/ov040/calls/DrawAreaRewardModel.c](../src/overlays/ov040/calls/DrawAreaRewardModel.c).

```c
void DrawAreaRewardModel(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Draws the area reward scene model with its embedded camera and explicit projection bounds top0x2400,bottom-0x2400,left-0x3000,right0x3000. Source: [eu/src/overlays/ov040/calls/DrawAreaRewardModel.c:1-10](../src/overlays/ov040/calls/DrawAreaRewardModel.c).
- The callee draws with temporary camera/projection and restores global projection/camera state. Source: [src/arm9/graphics/DrawNodeWithExplicitProjection_0202f1b0.c:1-38](../../src/arm9/graphics/DrawNodeWithExplicitProjection_0202f1b0.c).
- The matching constructor owns the exact data_ov040_020be280 model/work pointer. Source: [eu/src/overlays/ov040/calls/InitAreaRewardScene.c:1-24](../src/overlays/ov040/calls/InitAreaRewardScene.c).

Contract limits:

- Does not draw arbitrary actor models.

## StartAreaEventsAdapter

Identity: `ov040:020bdba4`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov040_020bdba4`.

EU entrypoint: [eu/src/overlays/ov040/calls/StartAreaEventsAdapter.c](../src/overlays/ov040/calls/StartAreaEventsAdapter.c).

```c
void * StartAreaEventsAdapter();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Forwards to StartCurrentAreaEvents. Source: [src/ov040/library_nitro_pxi/PXI_Init_020bdb84.c:1-5](../../src/ov040/library_nitro_pxi/PXI_Init_020bdb84.c).

Contract limits:

- No PXI operation occurs.

## RewardCodeToStackItemId

Identity: `ov040:020bdc44`, THUMB, native extent 112 bytes (including any configured pool). Previous symbol: `func_ov040_020bdc44`.

EU entrypoint: [eu/src/overlays/ov040/calls/RewardCodeToStackItemId.c](../src/overlays/ov040/calls/RewardCodeToStackItemId.c).

```c
u32 RewardCodeToStackItemId(u32 code);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Maps contiguous reward codes0x1e0..0x1ed to stack item IDs0xcb..0xd8; unsupported codes return-1. Source: [eu/src/overlays/ov040/calls/RewardCodeToStackItemId.c:1-52](../src/overlays/ov040/calls/RewardCodeToStackItemId.c).
- Uses the result as StackSlot.id before AddToStackSlot and possible replacement. Source: [src/ov040/shared_engine/GrantRewardItem_020be02c.c:1-58](../../src/ov040/shared_engine/GrantRewardItem_020be02c.c).
- Compares the same result with stored slot IDs. Source: [src/ov040/shared_engine/IsRewardSlotUnclaimed_020be0c4.c:1-21](../../src/ov040/shared_engine/IsRewardSlotUnclaimed_020be0c4.c).

Contract limits:

- Not a session flag index even though some old locals are called flagId.

## InitAreaRewardResources

Identity: `ov040:020bdf9c`, THUMB, native extent 112 bytes (including any configured pool). Previous symbol: `func_ov040_020bdf9c`.

EU entrypoint: [eu/src/overlays/ov040/calls/InitAreaRewardResources.c](../src/overlays/ov040/calls/InitAreaRewardResources.c).

```c
void InitAreaRewardResources(int actor,u32 owner);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Allocates20bytes, acquires two record handles for archive4 file indices0/14 plus palette entry0, and clears pending-item word+0x0c. Source: [eu/src/overlays/ov040/calls/InitAreaRewardResources.c:1-26](../src/overlays/ov040/calls/InitAreaRewardResources.c).
- The actor resource constructor invokes this only in field mode6, using its cue manager at actor+0x1070. Source: [src/ov053/object_factory/LoadOverlay053EntityResources_020d2414.c:1-122](../../src/ov053/object_factory/LoadOverlay053EntityResources_020d2414.c).
- The exact same global allocation stores pending item+0x0c and timer+0x10. Source: [src/ov040/shared_engine/ShowRewardPopupForItem_020be0f8.c:1-47](../../src/ov040/shared_engine/ShowRewardPopupForItem_020be0f8.c).
- The reward grant clears the same pending-item word after completion. Source: [src/ov040/shared_engine/GrantRewardItem_020be02c.c:1-58](../../src/ov040/shared_engine/GrantRewardItem_020be02c.c).

Contract limits:

- One allocation has both resource-handle prefix and reward-popup state; this is established by identical global owner, not offset analogy.
- The fifth word timer+0x10 is not initialized by this constructor.
- Does not initialize the whole actor or animation storage.

## GetAreaRewardAnimationTable

Identity: `ov040:020be028`, THUMB, native extent 20 bytes (including any configured pool). Previous symbol: `func_ov040_020be028`.

EU entrypoint: [eu/src/overlays/ov040/calls/GetAreaRewardAnimationTable.c](../src/overlays/ov040/calls/GetAreaRewardAnimationTable.c).

```c
u8 * GetAreaRewardAnimationTable(int index);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns recordHandle[index].state+8 from the shared area reward resource allocation. Source: [eu/src/overlays/ov040/calls/GetAreaRewardAnimationTable.c:1-7](../src/overlays/ov040/calls/GetAreaRewardAnimationTable.c).
- In mode6 without a reaction record, caller selects index0/1 and passes this table to ChangeActorState. Source: [src/ov052/unclassified_helpers/RequestActorMode_020cde20.c:1-106](../../src/ov052/unclassified_helpers/RequestActorMode_020cde20.c).
- RecordHandle first word is its SharedRecordState allocation. Source: [src/ov021/object_state/AcquireRecordHandle_020adaf0.c:1-47](../../src/ov021/object_state/AcquireRecordHandle_020adaf0.c).

Contract limits:

- Only indices0/1 are proven by this caller; slot2 is a different palette-entry type.
- The pointer is borrowed animation-table storage; not the RecordHandle itself.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov040/calls/SetAreaBugCollisionEnabledByLevel.c SetAreaBugCollisionEnabledByLevel --thumb
python tools/verify_idx.py src/overlays/ov040/calls/RefreshAreaEventObjectAndLayerState.c RefreshAreaEventObjectAndLayerState --thumb
python tools/verify_idx.py src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c IsStageObjectExcludedFromAreaGroups --thumb
python tools/verify_idx.py src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c ConfigureAreaSceneSlotsAndReset --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c AreaSceneState_WaitForPanelReady --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c AreaSceneState_SetTransitionAudioAndFlags --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_BeginScreenTransition.c AreaSceneState_BeginScreenTransition --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_RestoreFieldWhenScreenIdle.c AreaSceneState_RestoreFieldWhenScreenIdle --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_StartIdleObjects.c AreaSceneState_StartIdleObjects --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c AreaSceneState_BeginFadeOut --thumb
python tools/verify_idx.py src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c AreaSceneState_WaitForExitTransition --thumb
python tools/verify_idx.py src/overlays/ov040/auto/AreaSceneState_Hold.c AreaSceneState_Hold --thumb
python tools/verify_idx.py src/overlays/ov040/calls/DrawAreaRewardModel.c DrawAreaRewardModel --thumb
python tools/verify_idx.py src/overlays/ov040/calls/StartAreaEventsAdapter.c StartAreaEventsAdapter --thumb
python tools/verify_idx.py src/overlays/ov040/calls/RewardCodeToStackItemId.c RewardCodeToStackItemId --thumb
python tools/verify_idx.py src/overlays/ov040/calls/InitAreaRewardResources.c InitAreaRewardResources --thumb
python tools/verify_idx.py src/overlays/ov040/calls/GetAreaRewardAnimationTable.c GetAreaRewardAnimationTable --thumb
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The full
108-function block passes the fresh gate for all 108 linked modules. Affected
function bytes, resolved relocation targets/types and addends, and all module
hashes match the preserved baseline. Native signatures and algorithms are
unchanged; verified-library receipts remain current.
