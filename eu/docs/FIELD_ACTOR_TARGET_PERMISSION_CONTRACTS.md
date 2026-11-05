# Field actor, target, permission and script contracts

This block names 23 previously numeric EU overlay 001 functions and corrects
one command previously assigned to the wrong manager. All 24 entrypoints are
Thumb. Names follow checked storage owners, callers and native consumers.

The source paths below are relative to `eu/`. Logical signatures describe the
demonstrated ABI; this naming block preserves existing C types and behavior.
New record labels explain contracts without defining a portable public layout.

## Actor-work ownership and native layout

`data_ov001_020a04bc` owns the managed-actor work. Creation initializes the mode
to -1, clears three entry records at +0x04 with native stride 0x28, initializes
entry updates to 1 at +0x8c, and sets the update step at +0x9c to FX12 one
(0x1000). The entry count is at +0x7c. An inherited view declaring four entries
would overlap that count; it must not be adopted as a portable layout without
checking all users. There is no new bounds validation in these accessors.

`InitPartyState` stores the requested mode, chooses actor factories and loaded
overlays, and forces mode 2 when more than one player selection is present.
`UpdatePartyState` dispatches primary contact work for modes 0/2 and the guarded
menu-page refresh for mode 1. These numeric modes are not assigned speculative
gameplay labels. The separate signed session byte at +0x18 is another domain.

The contact record at actor work +0xdc has a native size of 20 bytes:

| Native offset | Demonstrated content and lifetime |
|---|---|
| +0x00 | Borrowed `WorldNamedEntry` pointer for contact |
| +0x04 / +0x08 | Low/high words of the OS contact tick |
| +0x0c | Borrowed pending data pointer copied from `WorldNamedEntry` +0x10 |
| +0x10 | Signed group-member index, -1 sentinel |

Native `UpdateTriggerWallContact` stores OS_GetTick's R0/R1 at +0x04/+0x08;
`UpdateActorTargetLink` also writes the pending pointer at +0x0c. Full reset
clears that pointer and writes the member sentinel; partial reset retains both.
The getter at 0x0206e644 reads the same pending pointer at actor work +0xe8.
Scene consumers test it and read bytes 1, 2 and 3; overlay 032 uses byte 2 as
route direction and passes bytes 1/3 to the session byte pair at +0x2744/0x2745.
Those observations do not prove names for the remaining payload fields or a
larger payload format. Keep native tick words explicit or otherwise preserve
this layout: host `u64` alignment must not silently move the pointer/index.

`LoadModeSprites` writes ten signed group IDs at +0xa0 through +0xb3. Observed
indexed callers use 0 through 9. `CreateFieldEffectGroups` creates two adjacent
groups at +0xb4/+0xb6, but that does not establish an indexed API capacity of 12.
The array of seven shared sprite slots is separately owned at +0xfc. It is
allocated as seven native 0x30-byte records, initialized and positioned through
the shared base getter, released entry by entry, then freed and cleared during
`DestroyPartyState`. Borrowed pointers expire with this owner.

The update gate at +0x8c controls `UpdatePartyEntries`, including its actor,
probe, level-up and slot-use recovery pass. It does not stop every renderer or
all of `UpdatePartyState`. The setter stores the complete input word; its script
adapter alone normalizes nonzero to 1. The script adapter
`ScriptCmd_SetPartyEntryUpdatesEnabled` now identifies that exact owner. Pool/class managers at globals
`data_ov001_020a04f8` and `data_ov001_020a04fc` have different ownership.

## Resource and animation boundaries

The offset-table destructor frees both its loaded file and its separately
allocated four-byte holder at `data_ov001_020a049c`. It does not destroy the
neighboring task or timer owners. Cursor cleanup releases six sprite resources;
the separate pair cleanup releases two. Neither frees the surrounding task
work. Cursor key changes restart a corner-spread tween from 45 FX12 units to
zero. The same key still selects the default center sprite without restarting
the tween. The tween parameter 400 is retained without asserting milliseconds.
The key is an opaque comparison value supplied by packed stage/slot or pool
selection; it is not uniformly an actor ID or a pointer to dereference.

The brightness setter changes the FX12 increment read by `ScreenFadeInStep`.
That consumer adds the increment to brightness and clamps at zero. The setter
does not start the fade, reset progress or validate the increment.

## Exact permission rules

`IsPartyGaugeGainAllowed` is a permission used by `AwardPartyGaugePoints` before
`AddGaugePoints`, as well as by highlight and item-reward consumers. With either
flag 0x3609 or 0x360a set, count must be greater than two. Otherwise flag 0x360b
blocks gain; session kind 7 with flag 0x370c or with flag 0x370d also blocks it.
Keep the branch precedence: the party-size branch excludes the later checks.
Callers retain their own actor, gauge and session validation.

`IsPoolAndStageSlotTargetSearchAllowed` returns false only when flags 0x3609
and 0x360a are both clear and flag 0x360b is set. The actual consumers search
kind-3 pool entries and kind-1 stage/slot entries. The kind-2 field-object
scanner is separate, so this is not a switch for every target family.

`IsSlotItemUseRecoveryAllowed` requires flags 0x3308 and 0x35e5 clear, session
mask 0x20 clear, session BGM mode at +0x27f8 different from 1, and a clear field
track flag. Both callers guard `AddSlotItemUses`, whose actual body calls
`RefillSlotItemUses` and updates the selected slot's uses byte. This policy
neither validates an individual item nor replaces its maximum-use handling.
The meanings of the numeric session flags are deliberately left unassigned.

## Panel, HUD and VM boundaries

The panel map gate requires loaded mode 0 and panel phase 3, 4 or 6. Its callers
then invoke the real overlay 023 map routines. It is distinct from the mode-2
list-ready field and from the phase-6-only scroll gate. The panel pointer is a
real logical input even where an inherited declaration erased it.

The counter HUD getter reads `fadeState` at +0x04, independently of the main HUD
state at +0x00 or the `fadeEnabled` flag. It returns zero if the HUD is absent.
The group-2 opcode 0x2f resume handler is paired with `ScriptCmd_ShowHudIndicator`
and completes when this state is zero. MAIN `ScriptVm_RunFrame` advances a
suspended command on resume return 1; it retains the command on resume return 0.
A null resume is retained for the run handlers in this block. Handler return 1
means command advance, not a delegated operation's success or resource ownership.

The camera-bound adapter resolves to overlay 042. Its setter writes min/max X,
uses the INT_MAX sentinel and invalidates follow caches; `UpdateCameraScene`
clamps goal.x against those exact bounds. The owner is not the similarly named
overlay 001 channel context. The stats command calls the no-input helper that
gets selection record 0 and computes its player stats. The stage reset command
reads one integer and passes its low 16 bits through the adapter to the already
named guarded operation. Inactive service means that operation can be a no-op,
while the script command still returns 1.

## Owned resources and target cursor

| EU identity | Name | Source relative to `eu/` | Logical contract and boundary | Evidence |
|---|---|---|---|---|
| ov001:0x02069508 (Thumb) | `ReleaseOffsetTableFile` | `src/overlays/ov001/calls/ReleaseOffsetTableFile.c` | `void(void)`. Frees the loaded offset-table file, then its holder, and clears global `data_ov001_020a049c`; absent holder is a no-op. Boundary: Does not act on task-owned timer/task globals `data_ov001_020a0494`/`data_ov001_020a0498`; file and holder are both released. | LoadOffsetTableFile allocates the same 4-byte holder, loads/rebases its file and stores global `data_ov001_020a049c`; ShutdownFieldSession invokes this destructor. |
| ov001:0x0206a8c8 (Thumb) | `SetScreenFadeBrightnessStepFx12` | `src/overlays/ov001/auto/SetScreenFadeBrightnessStepFx12.c` | `void(fx32 step)`. Stores the raw 32-bit brightness step at screen work +0x1c. Boundary: Does not start a fade, reset progress or clamp the new step; screen work at `data_ov001_020a04a0` must exist. | ScreenFadeInStep reads this exact field as brightnessStep, adds it to fixed-point brightness, and clamps brightness at 0; transition callers pass FX_Div(16*ONE,32/64*ONE). |
| ov001:0x0206bf34 (Thumb) | `ReleaseTargetCursorResources` | `src/overlays/ov001/calls/ReleaseTargetCursorResources.c` | `void(TargetCursor *cursor)`. Releases four corner-sprite and two center-sprite resource records, resets spread state/key and initializes the embedded tween. Boundary: Does not free outer target task work or clear the current-center pointer+0x120; preserve release order and tween reset. | InitButtonPanelSprites initializes the same six 0x30-byte records; UpdateCornerSpread/PlaceCornerItems render them. ShutdownSceneWork passes target-work+0xcc. |
| ov001:0x0206bfec (Thumb) | `SelectDefaultTargetCursorForKey` | `src/overlays/ov001/calls/SelectDefaultTargetCursorForKey.c` | `void(TargetCursor *cursor, u32 key)`. Selects first center sprite at +0xc0. For a changed key at +0x128, enters spread state 1 at +0x124 and starts tween(mode 2,45*ONE,0,400). Boundary: Same-key calls still select the center sprite but do not restart the animation. Key is an opaque 32-bit comparison value, not necessarily an actor ID or pointer to dereference. | ApplyPendingTargetRequest supplies packed stage-id/slot or a pool-entry key. UpdateCornerSpread consumes state 1/tween and places/draws the corner sprites. |
| ov001:0x0206c204 (Thumb) | `ReleaseTargetSpritePairResources` | `src/overlays/ov001/calls/ReleaseTargetSpritePairResources.c` | `void(TargetSpritePair *pair)`. Releases the two 0x30-byte sprite resources. Boundary: Does not free outer task work or reset the pair tween; separate from the six-sprite cursor cleanup. | InitSpritePairFromResource builds both from resource group 7 entries 0/1; SetupMirroredObjectPair positions/draws them. ShutdownSceneWork passes target-work+0x50. |

## Actor work, contact record and shared resources

| EU identity | Name | Source relative to `eu/` | Logical contract and boundary | Evidence |
|---|---|---|---|---|
| ov001:0x0206cdec (Thumb) | `ResetWorldEntryContactState` | `src/overlays/ov001/calls/ResetWorldEntryContactState.c` | `void(WorldEntryContactState *state, BOOL fullReset)`. Clears contact entry and the two words of its 64-bit contact tick. Full reset additionally clears pending entry-data pointer and sets group member index to-1. Boundary: Native record is 20 bytes at event work +0xdc: pointer,tick low word,tick high word,pending pointer,s32 member index. Partial reset deliberately retains the last two fields; no ownership transfer/free. | Native UpdateTriggerWallContact stores OS_GetTick R0/R1 at +0x04/+0x08 and copies entry+10 to+0x0c; UpdateActorTargetLink also writes+c. CreatePartyState/ReleaseActorSlotByIndex use full reset; UpdatePrimaryEventRecord uses partial reset. |
| ov001:0x0206d2dc (Thumb) | `RefreshPrimaryActorMenuPage` | `src/overlays/ov001/calls/RefreshPrimaryActorMenuPage.c` | `void(void)`. Refreshes field menu page only when primary-entry flag 0x08 is set, flag 0x10 clear and pending world-entry data+0x0c of record +0xdc is null. Boundary: Original forwarded actor word is incidental to a no-input callee. Context must exist; this is not a general actor-idle or resource-ready predicate. | UpdatePartyState selects this pass for managed-actor mode 1. RefreshFieldMenuPage resolves current target state and selects the page; its real contract is void(void). |
| ov001:0x0206db44 (Thumb) | `GetFieldActorUpdateStepFx12` | `src/overlays/ov001/calls/GetFieldActorUpdateStepFx12.c` | `fx32(void)`. Returns event work +0x9c, default ONE when context is absent. Boundary: Per-update FX12 step/scale, not OS milliseconds. Return is unnormalized and has no positivity clamp. | CreatePartyState initializes +0x9c=0x1000; UpdatePartyEntries stores its update argument there. ApplyTimeScaledSpeed uses FX_Mul with it; actor/AI updates accumulate or subtract it from fixed-point frame values. |
| ov001:0x0206db8c (Thumb) | `GetFieldEntryGroupId` | `src/overlays/ov001/calls/GetFieldEntryGroupId.c` | `s32(int index)`. Returns signed 16-bit group ID at event work +0xa0+index*2. Boundary: No context/index check; preserve signed-16 extension. Observed indexed consumers use 0 through 9. Adjacent effect groups at +0xb4/+0xb6 are separately written and do not prove an indexed API capacity. | LoadModeSprites writes ten IDs +0xa0 through +0xb3 from the entry-group constructor; callers pass them to InitializeEntryGroupSlot, IsGroupMemberActive, entry-slot creation/release APIs. |
| ov001:0x0206dc20 (Thumb) | `GetSharedFieldSpriteSlots` | `src/overlays/ov001/calls/GetSharedFieldSpriteSlots.c` | `FieldSpriteSlot *(void)`. Returns the borrowed sprite-slot base at event work +0xfc, or null with no context. Boundary: Getter neither allocates nor transfers ownership. Do not retain pointers after manager teardown or use the old idleTimer field label for+0xfc. | LoadManagerSpriteSlots allocates seven 0x30-byte slots and initializes each; BindHudNodeOffsets/InitFieldSpriteSlots bind positions/scales to them; DestroyPartyState releases all 7 and frees/clears the base. |
| ov001:0x0206e5a4 (Thumb) | `SetPartyEntryUpdatesEnabled` | `src/overlays/ov001/calls/SetPartyEntryUpdatesEnabled.c` | `void(u32 value)`. If event context exists, writes full input word to+0x8c. Boundary: Only this update pass is gated; not all rendering or UpdatePartyState work. Setter does not normalize the stored word or modify entry flags. | CreatePartyState initializes the same word to 1; UpdatePartyEntries returns before actor/probe/level-up/refill work when it is 0. The script caller normalizes its operand before forwarding. |
| ov001:0x0206e62c (Thumb) | `GetManagedActorMode` | `src/overlays/ov001/calls/GetManagedActorMode.c` | `s32(void)`. Returns managed-actor mode word +0x00, or -1 when context is absent. Boundary: A dispatch/loading mode, not selected actor index or the separate session-kind byte at session+18. Further gameplay labels for 0/1/2 are not assigned. | CreatePartyState initializes -1; InitPartyState stores its mode argument, overrides it to 2 for multiple selections, chooses actor factory/overlays; UpdatePartyState dispatches primary contact work for 0/2 and menu refresh for 1. |
| ov001:0x0206e644 (Thumb) | `GetPendingWorldEntryData` | `src/overlays/ov001/calls/GetPendingWorldEntryData.c` | `const u8 *(void)`. Returns the borrowed pending world-entry data pointer at event work +0xe8, or null without context. Boundary: Native result is a pointer, not a normalized readiness flag or enum. Payload minimum accessed span is four bytes; field names beyond observed consumers/encoding are not invented. | Native writers copy WorldNamedEntry+10 to contact-record+c, immediately in UpdateActorTargetLink or after timed contact in UpdateTriggerWallContact. Eight scene consumers test the pointer; ov032 reads byte 2 as route direction and bytes 1/3 for session +0x2744/+0x2745. |

## Permission policies

| EU identity | Name | Source relative to `eu/` | Logical contract and boundary | Evidence |
|---|---|---|---|---|
| ov001:0x0206e224 (Thumb) | `IsPartyGaugeGainAllowed` | `src/overlays/ov001/calls/IsPartyGaugeGainAllowed.c` | `BOOL(void)`. Applies mode/session/party-size policy used to permit party gauge point gain. Boundary: Permission only: caller separately checks actor/session/gauge conditions. Preserve short-circuit order and the numeric flag/mode rules; no broader game-mode labels. | AwardPartyGaugePoints forces points=0 when false before AddGaugePoints. UI highlight and item-reward consumers use the same rule. Flags 0x3609/0x360a require count>2;360b blocks; mode 7 flags 0x370c/0x370d add restrictions. |
| ov001:0x0206e280 (Thumb) | `IsPoolAndStageSlotTargetSearchAllowed` | `src/overlays/ov001/calls/IsPoolAndStageSlotTargetSearchAllowed.c` | `BOOL(void)`. Returns false only when flags 0x3609/0x360a are both clear and flag 0x360b is set. Boundary: Does not enable/disable every target family or alter selection flags. Numeric flag meanings are left unassigned. | ScanObjectsForNearestTarget and FindBestEventSlotTarget both return early when false; their target constructors use kind 3 PoolEntry and kind 1 stage-id/slot. The FieldObject kind 2 scanner is separate. |
| ov001:0x0206e2d0 (Thumb) | `IsSlotItemUseRecoveryAllowed` | `src/overlays/ov001/calls/IsSlotItemUseRecoveryAllowed.c` | `BOOL(void)`. Permits slot-use recovery only with session flags 0x3308/0x35e5 clear, session mask 0x20 clear, BGM mode!=1 and no field-track flag. Boundary: A global permission rule, not an item-validity/max-use check. Preserve current BGM/field flags and pending transition blockers; do not reduce it to a generic out-of-battle Boolean. | UpdatePartyEntries guards AddSlotItemUses over active item slots with this predicate; ApplyItemRewardEffect also guards the same operation. AddSlotItemUses calls RefillSlotItemUses then increments the selected slot uses byte. |

## Panel and HUD state

| EU identity | Name | Source relative to `eu/` | Logical contract and boundary | Evidence |
|---|---|---|---|---|
| ov001:0x0207a8fc (Thumb) | `IsPanelMapUpdateAllowed` | `src/overlays/ov001/calls/IsPanelMapUpdateAllowed.c` | `BOOL(const SubscenePanel *panel)`. Returns true only for loaded mode 0 and panel phases 3, 4 or 6. Boundary: Map gate distinct from mode 2 list readiness+38 or phase-6-only scroll gate. Real panel input must survive legacy no-argument declarations; no resource-completion guarantee. | SetPanelMapEntry/RequestPanelMapReset/UpdatePanelMapRangePosition/MarkPanelMapTransformDirty and formation/header adapters gate real ov023 map calls with this predicate. |
| ov001:0x0207d4e4 (Thumb) | `GetCounterHudFadeState` | `src/overlays/ov001/calls/GetCounterHudFadeState.c` | `u32(void)`. Returns CounterHud fadeState word +0x04, or 0 when HUD work is absent. Boundary: Raw state, not normalized Boolean and not main HUD state+0. No ownership transfer or allocation. | CounterHud.h declares fadeState at +0x04; UpdateAndDrawCounterHud indexes gFadeSequenceHandlers with it when fadeEnabled. AccumulateCounterHudDelta separately checks fadeState 2. |

## Script adapters and their delegated operation

| EU identity | Name | Source relative to `eu/` | Logical contract and boundary | Evidence |
|---|---|---|---|---|
| ov001:0x02065758 (Thumb) | `ScriptCmd_WaitForCounterHudFadeState0` | `src/overlays/ov001/calls/ScriptCmd_WaitForCounterHudFadeState0.c` | `int(void)`. Returns 1 when CounterHud fadeState is 0 (including absent HUD), otherwise 0. Boundary: No logical operands; VM resume arguments are unused. Does not initialize HUD or start/change its fade. | gFieldScriptCommandHandlers group 2 entry 2f installs this as resume paired with ScriptCmd_ShowHudIndicator. MAIN VM advances the suspended command on resume return 1. |
| ov001:0x020657a4 (Thumb) | `ScriptCmd_SetCameraHorizontalFollowBounds` | `src/overlays/ov001/calls/ScriptCmd_SetCameraHorizontalFollowBounds.c` | `int(ScriptVm *vm, ScriptOperand *operands)`. Reads two FX32 operands at +0/+8 and forwards them to horizontal camera follow bounds, then returns 1. Boundary: Owner is ov042 camera, not ov001 gActorChannelContext. Preserve sentinel/cache transitions and operand order; command advance is not a validity result. | Actual callee is in ov042: it writes minX/maxX at +0xc4/+0xc8 of data_ov042_020be5e0, handles INT_MAX sentinel and invalidates follow caches; UpdateCameraScene clamps goal.x using those fields. |
| ov001:0x02065e44 (Thumb) | `ScriptCmd_RefreshFirstSelectionPlayerStats` | `src/overlays/ov001/calls/ScriptCmd_RefreshFirstSelectionPlayerStats.c` | `int(void)`. Calls RefreshFirstSelectionPlayerStats and returns 1. Boundary: Inherited forwarded VM pointer is not a stats input. No decoded operands, returned allocation or propagated stats result. | Real no-input callee obtains selection record 0 and calls ComputePlayerStats(saveGlobal,out,0,1). Registered group 2 entry 53 is a run handler with null resume. |
| ov001:0x020655d8 (Thumb) | `ScriptCmd_ResetStageGroupRowsAndRestoreDefault` | `src/overlays/ov001/calls/ScriptCmd_ResetStageGroupRowsAndRestoreDefault.c` | `int(ScriptVm *vm, ScriptOperand *operands)`. Reads one integer operand, forwards through the low 16-bit reset adapter and returns 1. Boundary: No added service/index guard in script wrapper. Full operand is decoded before narrowing; advancing the VM does not prove reset occurred. | Adapter at 0x0206890c calls the already validated ResetStageGroupRowsAndRestoreDefaultIfActive; its two ordered callees reset rows and restore the selected slot default. |
| ov001:0x0206890c (Thumb) | `ResetStageGroupRowsAndRestoreDefault` | `src/overlays/ov001/calls/ResetStageGroupRowsAndRestoreDefault.c` | `void(u32 groupIndex)`. Forwards low 16 bits of group index to ResetStageGroupRowsAndRestoreDefaultIfActive. Boundary: Preserve u16 mask and zero-based index boundary. This helper does not create the manager or guarantee action when service is inactive. | Paired script wrapper at 0x020655d8 is the caller; validated stage adapter applies service-active guard then ResetGroupRows and RestoreStageSlotDefault in that order. |

## Correction of an existing descriptive name

| EU identity | Previous name | Corrected name | Source relative to `eu/` | Contract |
|---|---|---|---|---|
| ov001:0x020655f8 (Thumb) | `ScriptCmd_SetPartyEntryUpdatesEnabled` | `ScriptCmd_SetPartyEntryUpdatesEnabled` | `src/overlays/ov001/calls/ScriptCmd_SetPartyEntryUpdatesEnabled.c` | `int(ScriptVm *vm, ScriptOperand *operands)`. Reads one integer operand, normalizes nonzero to 1, invokes the raw-word party-entry update setter and returns 1. Group 2 opcode 0x26 run handler; no resume. |

## Dispatch identities

| Handler | Group | Opcode | Role | Paired handler |
|---|---|---|---|---|
| `ScriptCmd_WaitForCounterHudFadeState0` | 2 | 0x2f | resume | `ScriptCmd_ShowHudIndicator` |
| `ScriptCmd_SetCameraHorizontalFollowBounds` | 2 | 0x32 | run | `NULL` |
| `ScriptCmd_RefreshFirstSelectionPlayerStats` | 2 | 0x53 | run | `NULL` |
| `ScriptCmd_ResetStageGroupRowsAndRestoreDefault` | 2 | 0x24 | run | `NULL` |
| `ScriptCmd_SetPartyEntryUpdatesEnabled` | 2 | 0x26 | run | `NULL` |

## Porting limits

Native pointer returns and borrowed pointers must remain pointers when the port
introduces real types; several inherited EU shims still expose them as 32-bit
words. A native ABI compatibility declaration is not a portable structure
contract. Preserve the contact record's 20-byte layout, 0x28 entry stride,
0x30 sprite-resource stride, signed-16 group IDs, full-word gate behavior,
FX12 arithmetic and explicit narrowing in the stage reset adapter. The
logical signatures above do not authorize mass prototype or layout rewrites.

Owners, null behavior, unchecked indices, partial-reset retention and caller
validation are stated per operation. No new ownership transfer, clamping,
parameter, extra callback result, gameplay flag label or index validation is
introduced by these names. Further type repairs need their own native-layout
and byte-exact checks.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseOffsetTableFile.c ReleaseOffsetTableFile --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SetScreenFadeBrightnessStepFx12.c SetScreenFadeBrightnessStepFx12 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseTargetCursorResources.c ReleaseTargetCursorResources --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SelectDefaultTargetCursorForKey.c SelectDefaultTargetCursorForKey --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseTargetSpritePairResources.c ReleaseTargetSpritePairResources --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetWorldEntryContactState.c ResetWorldEntryContactState --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RefreshPrimaryActorMenuPage.c RefreshPrimaryActorMenuPage --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldActorUpdateStepFx12.c GetFieldActorUpdateStepFx12 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldEntryGroupId.c GetFieldEntryGroupId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSharedFieldSpriteSlots.c GetSharedFieldSpriteSlots --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetPartyEntryUpdatesEnabled.c SetPartyEntryUpdatesEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetManagedActorMode.c GetManagedActorMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPendingWorldEntryData.c GetPendingWorldEntryData --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsPartyGaugeGainAllowed.c IsPartyGaugeGainAllowed --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsPoolAndStageSlotTargetSearchAllowed.c IsPoolAndStageSlotTargetSearchAllowed --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsSlotItemUseRecoveryAllowed.c IsSlotItemUseRecoveryAllowed --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsPanelMapUpdateAllowed.c IsPanelMapUpdateAllowed --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetCounterHudFadeState.c GetCounterHudFadeState --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_WaitForCounterHudFadeState0.c ScriptCmd_WaitForCounterHudFadeState0 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetCameraHorizontalFollowBounds.c ScriptCmd_SetCameraHorizontalFollowBounds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_RefreshFirstSelectionPlayerStats.c ScriptCmd_RefreshFirstSelectionPlayerStats --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ResetStageGroupRowsAndRestoreDefault.c ScriptCmd_ResetStageGroupRowsAndRestoreDefault --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetStageGroupRowsAndRestoreDefault.c ResetStageGroupRowsAndRestoreDefault --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetPartyEntryUpdatesEnabled.c ScriptCmd_SetPartyEntryUpdatesEnabled --thumb
bash tools/gate.sh
```
