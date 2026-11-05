# Field HUD resources, command menu, minigame and entry-pool contracts

This block names 46 previously numeric EU overlay 001 Thumb functions. Names
follow checked owner storage, constructors, callback registration and actual
consumers. The source paths below are relative to `eu/`.

Signatures describe logical inputs and returns demonstrated by the code and
native ABI. New type labels here describe contracts; this naming block does
not introduce new public layouts or mass prototype repairs. Several existing
shims use 32-bit integers as pointer carriers or erase callee arguments. Their
spelling is not evidence for a portable API.

## Four separate owners

| Owner | Demonstrated role |
|---|---|
| Field scene pointer at `data_ov001_020a04c4` +4 | HUD/window/message resources, selected location name/list and installed minigame callbacks |
| Menu pointer at `data_ov001_020a04d0` +4 | Command-menu presentation, active list, cursor, delayed button records |
| `data_ov001_020a04f4` | Field minigame work, mode, active round, binary-angle prompt, score and level |
| `data_ov001_020a04fc` | Entry-pool registry, active node list, resource-delivery state and mode-selected reward tables |
| `data_ov001_020a04f8` | Separate class-based field-object manager, feature-bit field and shared shadow model |

The two field-object families have different object layouts and callback tables.
Class-object callbacks from the +0x04f8 family must not be substituted for pool
callbacks merely because some old C views call both objects `FieldObject`.

## Resource lifetimes and shared window storage

`InitFieldHudWindow` pairs message view +0x50c, palette-copy buffer +0x5c0 and
embedded window +0x584 with their cleanup. `BuildMessageLineWindow` owns the
window +0xa8 and its 22 cached line surfaces; cleanup clears the surface pointers
but retains adjacent message IDs. `LoadRecordNamesAndEntryList` owns windows
+0x18c/+0x1c0, the separate line-pointer array, 512 copied UTF-16 names and the
cloned world-selected list record. Its current-name pointer at +0x1334 aliases
one of those name copies. The record getter at +0x1338 and name getter do not
extend those lifetimes. A caller retaining either after cleanup would have a
stale pointer even if the inherited C uses a raw word return.

The four-choice window and the temporary slot-label header both begin at
+0x1fc in different phases. `ReleaseFieldChoiceWindow` destroys one choice
window after its caller checks active state. `ReleaseSlotLabelWindowsAndMessages`
destroys a header and a slot-count-plus-one series, then accompanies restoration
of the saved HUD layers. Their shared address does not make their lifetime or
number of windows interchangeable. Window cleanup does not free the outer
scene or the scene fonts. The +0x4d8/+0x51c windows have constructor identities
and native locations; their names preserve those useful distinctions while
leaving any unproved higher-level display label unassigned.

The three panel-screen cleanup wrappers are selected by script selectors 2/3/4.
They currently all call the same `ReleaseOverlayWidgets` implementation, which
destroys the panel task, clears its handle, updates the scene state, clears
widget layers 9/10/11 and unloads overlay 045. Their selector suffixes preserve
native identities without inventing three different cleanup behaviors. The
callee returns void; an inherited `void *` wrapper declaration does not provide
a logical pointer result.

## Menu modes, redraw and delayed records

Menu +0x68 is presentation/label mode, changed by `SetFieldMenuMode`; menu
+0x104 is list mode, changed by `SetFieldMenuMode_02078360`; +0xfc selects the
page draw handler. The getters distinguish these domains. List-mode switches
save/restore cursors and choose count/layout. The mode-2 cursor getter returns
+0xec only in that list mode and returns -1 otherwise.

The button delay is timer +0x144. Arming starts a negative timer at zero only
with at least two entries. Its true return means that policy guards permitted
the path, including the already-armed or fewer-entry cases; it does not promise
a new timer write. `UpdateFieldMenu` advances the timer only while its separate
+0x140 gate is nonzero, invokes `TriggerFieldMenuButtonRecords` at five updates
and leaves the timer at five. Cancellation sets it to -1 and invokes slot
+0x40 of three associated active records. The names do not assert that those
particular callbacks start or stop animations without their descriptor proof.

## Installed minigame protocol

`StartSceneMinigameTask` creates mode 1/2/3 tasks for selection scene IDs
0xc5/0xc6/0xca and installs a six-slot callback block beginning at scene +0x1340:
start, stop, input, active query, score and level. Thus +0x134c is the installed
active-query callback. Its invoker checks for a null callback and normalizes
nonzero; `IsFieldMinigameRoundActive` directly checks the separate minigame work
and active word +0x20. Stop hides timed counters, invokes record 0x12e callback
+0x40 and clears active without freeing the task or clearing score/level.

The mode-2 prompt initializer chooses one of four binary-angle quarter turns,
stores signed direction +1 and scale 0x400, and optionally binds shared sprite
slots. `UpdateSpinningMode` adds direction times scale modulo 0x10000.
`HandleDirectionalPrompt` maps angle sectors to keys. Positive names arithmetic
angle direction; it does not claim a screen-space clockwise orientation. The
mode-3 `RandomizeFacing` counterpart stores -1 direction.

## Entry-pool operations and delivery

Pool operations at owner +0x1c and +0x20 receive entry plus hit message or
three-component motion output and return raw status. Missing callbacks return
zero. They neither validate entry activity nor normalize backend results. The
motion backends include actor velocity copies and vertical three-word outputs;
no common absolute-position or velocity-unit contract is added. The hit
backends return different status/bit patterns; nonzero must not be reinterpreted
as universal acceptance or success.

The target-position dispatcher checks entry flag 0x08 before calling owner
+0x28, returning a borrowed top/raised/focus vector or null. A backend may reuse
shared scratch storage. The range getter separately requires the node flag bit
to be clear and entry flag 0x08, then returns owner +0x44 or -1. Constructors set
that range to 0x3000, and the facing/range consumer uses it as an FX12 distance
cap. An inherited structure member called `id` is not the semantic type.

Manager byte +0x04 is the signed pool count. The equivalent getter at
0x0208722c already has the name `GetFieldEntryPoolCount`; this block keeps
`GetFieldEntryPoolCount_02087270` for the second native entrypoint rather than
inventing a different purpose. Halfword +0x06 is the separate linked active-entry
count, maintained while appending/clearing nodes and used for map overflow
storage before map-specific filtering.

Explicit update blocking sets bit 0x01 and requests an offset reset through
bit 0x80. Conditional pause uses bit 0x40 with the same reset request; the updater
clears that pause when lead-entry mask 0x10 clears. The consumer's update mask
is 0x51, which also includes the existing independent cache pause bit 0x10.
Clearing either setter leaves a pending reset intact. These operations do not
claim to toggle every interaction or rendering path, even where an older caller
uses a visibility-oriented name.

Requested resource slots set queued bit 0x02. Delivery request sets 0x04/0x08;
`StepResourceSlotLoading` loads record/file pairs and invokes listener callbacks,
frees the temporary file and marks the entry delivered. It can yield false after
one callback, so requesting delivery does not mean all resources are ready.
Do not merge manager flags with the distinct per-entry load flags.

## Reward layout and class-manager resources

Mode-selected reward buffers come from record slot 6: a signed-halfword array
and six-byte records. Their getters return borrowed elements, enforce only an
upper bound, and retain the original absence of a negative-index check. Release
clears pointers without clearing counts. The six-word unlock request is native
24 bytes: skip-mode-check input, entry, drop-on-lock, drop-on-unlock, flag entry,
flag slot. Initialization exchanges the third/fourth incoming payload values in
storage; `GrantEntryUnlockReward` consumes the two drop branches differently.

The class manager's feature function takes a bit index, not an already shifted
mask, and matches the existing `ObjectManager_IsFlagBitSet` API. Individual
feature-bit meanings remain numeric. Its shadow getter returns a borrowed node
created from the mo/sd resource, positioned/scaled and drawn for non-volume
shadows. Reset releases linked class objects, clears the feature word, releases
and frees the shadow node, and releases the separate entry-pool resources. It
does not free the class manager or archive. Native 0x0207efba passes the shadow
node in R0 to `ReleaseResourceAndDetach`; the old no-argument C declaration
hides a real input and must not become the port's public contract.

## Scene windows, names and list resources

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x0206f2f8 (Thumb) | `ReleaseFieldHudTextResources`; `src/overlays/ov001/calls/ReleaseFieldHudTextResources.c` | `void(FieldScene *scene)`. Free message view +0x50c, free and clear palette-copy buffer +0x5c0, destroy HUD text window +0x584. | InitFieldHudWindow loads message view 2, allocates 0x60 palette-copy bytes and initializes the identical window; ShutdownFieldScene pairs cleanup. Limits: No outer-scene or font free. Preserve file/palette/window order. Evidence sources: `eu/src/overlays/ov001/calls/InitFieldHudWindow.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`. |
| ov001:0x0206f464 (Thumb) | `ReleaseFieldMessageLineWindow`; `src/overlays/ov001/calls/ReleaseFieldMessageLineWindow.c` | `void(FieldScene *scene)`. Destroy window +0xa8 and clear 22 cached line pointers at +0xdc, stride eight. | BuildMessageLineWindow initializes the same window and caches exactly 22 surfaces with adjacent message IDs; ShutdownFieldScene calls cleanup. Limits: Only line pointers are cleared; adjacent message IDs remain. Window destruction owns nested surfaces, not scene. Evidence sources: `eu/src/overlays/ov001/calls/BuildMessageLineWindow.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`. |
| ov001:0x0206f648 (Thumb) | `ReleaseFieldRecordNamesAndEntryList`; `src/overlays/ov001/calls/ReleaseFieldRecordNamesAndEntryList.c` | `void(FieldScene *scene)`. Destroy title/list windows +0x18c/+0x1c0, free line-pointer array +0x1f4 and 512 UTF-16 name copies +0xb34, release list record +0x1338. | LoadRecordNamesAndEntryList constructs all these resources. ReleaseResourceWithBuffers frees both record buffers and record, and clears the handle. Limits: Most freed name/line slots and current-name alias are not cleared. No scene free; inherited extra 0xe passed to the one-input record destructor is not a logical heap parameter. Evidence sources: `eu/src/overlays/ov001/calls/LoadRecordNamesAndEntryList.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`, `eu/src/calls/ReleaseResourceWithBuffers.c`. |
| ov001:0x0206f6cc (Thumb) | `ReleaseSceneTextWindow4D8`; `src/overlays/ov001/calls/ReleaseSceneTextWindow4D8.c` | `void(FieldScene *scene)`. Destroy embedded text window +0x4d8. | InitSceneTextWindow4D8 initializes the exact address using gSceneTextFrame4D8; ShutdownFieldScene pairs destruction. Limits: Offset suffix distinguishes an established window; no higher-level display purpose is asserted. No scene/font free. Evidence sources: `eu/src/overlays/ov001/calls/InitSceneTextWindow4D8.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`. |
| ov001:0x0206f720 (Thumb) | `ReleaseSceneTextWindow51C`; `src/overlays/ov001/calls/ReleaseSceneTextWindow51C.c` | `void(FieldScene *scene)`. Destroy embedded text window +0x51c. | InitSceneTextWindow51C initializes that address with BG3, widget layer 0xb and scene font; ShutdownFieldScene pairs cleanup. Limits: No outer-scene or font free. Offset suffix distinguishes it from other embedded text windows. Evidence sources: `eu/src/overlays/ov001/calls/InitSceneTextWindow51C.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`. |
| ov001:0x0206f848 (Thumb) | `ReleaseFieldChoiceWindow`; `src/overlays/ov001/calls/ReleaseFieldChoiceWindow.c` | `void(FieldScene *scene)`. Destroy choice window +0x1fc. | BuildChoiceWindow creates four surfaces there and sets choiceMenuActive +0x1f8; ShutdownFieldScene checks that state before invoking cleanup. Limits: No internal active/null check or state/pointer clearing. Temporary slot-label windows use the same +0x1fc storage in another phase. Evidence sources: `eu/src/overlays/ov001/calls/BuildChoiceWindow.c`, `eu/src/overlays/ov001/calls/ShutdownFieldScene.c`. |
| ov001:0x0206fa2c (Thumb) | `ReleaseSlotLabelWindowsAndMessages`; `src/overlays/ov001/calls/ReleaseSlotLabelWindowsAndMessages.c` | `void(FieldScene *scene)`. Free message views +0x2d8/+0x2cc, destroy header window +0x1fc and CountAssignedFieldSlots()+1 windows at +0x230 with stride 0x34. | BuildSlotLabelWindows constructs identical windows and persistent message views; UnloadHudLayersAndRecordText pairs cleanup before HUD restoration. Limits: Preserve count-plus-one loop and release order. No outer-scene free; separate phase from choice window sharing +0x1fc. Evidence sources: `eu/src/overlays/ov001/calls/BuildSlotLabelWindows.c`, `eu/src/overlays/ov001/calls/UnloadHudLayersAndRecordText.c`. |
| ov001:0x02073030 (Thumb) | `SetFieldHudBottomRowEnabled`; `src/overlays/ov001/calls/SetFieldHudBottomRowEnabled.c` | `void(s32 enabled)`. On guarded zero-to-nonzero request in loaded mode 0, load bottom-row tiles, then store full word +0x5c8. | InitFieldHudWindow tests identical bottomRowEnabled; LoadMenuBackground enables and DestroyFndListIfNonEmpty clears it. Limits: No normalization or immediate erase on disable. Load only on guarded rising edge. Scene must exist. Evidence sources: `eu/src/overlays/ov001/calls/InitFieldHudWindow.c`, `eu/src/overlays/ov001/calls/LoadFieldBottomRowTiles.c`, `eu/src/overlays/ov023/calls/LoadMenuBackground.c`, `eu/src/overlays/ov023/calls/DestroyFndListIfNonEmpty.c`. |
| ov001:0x02073060 (Thumb) | `GetFieldSceneEntryListRecord`; `src/overlays/ov001/calls/GetFieldSceneEntryListRecord.c` | `ListRecord *(void)`. Return borrowed record at +0x1338. | LoadRecordNamesAndEntryList clones the world-selected record there; ov053 iterates tags, ov021 uses tags to select motion blocks and ov025 uses the list data. Limits: No context/null check or ownership transfer. Record and buffers are destroyed during ReleaseFieldRecordNamesAndEntryList. Native word is pointer carrier. Evidence sources: `eu/src/overlays/ov001/calls/LoadRecordNamesAndEntryList.c`, `eu/src/overlays/ov053/calls/RegisterOverlay053TaggedEntries.c`, `eu/src/overlays/ov021/calls/RelocateUnitMotionData.c`, `eu/src/overlays/ov025/calls/InitMenuScreen.c`. |
| ov001:0x02073684 (Thumb) | `GetFieldSceneLocationName`; `src/overlays/ov001/calls/GetFieldSceneLocationName.c` | `const u16 *(void)`. Return borrowed current-name pointer +0x1334. | LoadRecordNamesAndEntryList selects names[worldBase[selection.world]+selection.room] and stores this alias; ov025 renders it as UTF-16. Limits: No copy/validation; expires with names array. Native u32 is not a numeric metric. Evidence sources: `eu/src/overlays/ov001/calls/LoadRecordNamesAndEntryList.c`, `eu/src/overlays/ov025/calls/SetupMenuTextLayers.c`, `eu/src/overlays/ov025/calls/DrawNumberInPanelSlot.c`. |

## HUD gauge range and packed patterns

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x0207162c (Thumb) | `SetFieldHudGaugeRange`; `src/overlays/ov001/calls/SetFieldHudGaugeRange.c` | `void(int slot, u16 maxValue, int value, int width)`. Forward range arguments through UpdateSlotRangeDefaultEnd with fixed fifth argument 7. | The adapter substitutes maxValue for zero width, then calls SetHudGaugeRange(force=false); core clamps value, retains old value for negative input, computes cells and updates the slot. Limits: Fixed 7 is a nonnegative notification parameter, not a slot count/gameplay enum. Inherited int result has no logical value from void callee. No extra index/divisor guard. Evidence sources: `eu/src/overlays/ov001/calls/UpdateSlotRangeDefaultEnd.c`, `eu/src/overlays/ov001/calls/SetHudGaugeRange.c`, `eu/src/overlays/ov001/calls/SetHudGaugeValue.c`, `eu/src/overlays/ov001/calls/UpdatePartyState.c`, `eu/src/overlays/ov001/calls/SetFieldSlotValue.c`. |
| ov001:0x020738b8 (Thumb) | `BlitGaugeFillPattern`; `src/overlays/ov001/calls/BlitGaugeFillPattern.c` | `void(u8 *tiles, int coordinate, const u8 *pattern)`. Call BlitNibbleRunPadded(tiles,coordinate,6,0x30,0,2,pattern). | DrawGaugeFill uses filled/two-transition/empty patterns before copying work tiles. Core blitter writes six pattern nibbles with tile-row stride four, preserving the other nibble. Limits: Coordinate is blitter right-coordinate, not byte offset. Preserve odd/even nibble and padding behavior; no bounds checks. Evidence sources: `eu/src/overlays/ov001/calls/DrawGaugeFill.c`, `eu/src/overlays/ov001/calls/BlitNibbleRunPadded.c`. |

## Script-selected panel-screen cleanup

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x02071ccc (Thumb) | `ReleaseFieldPanelScreen3Widgets`; `src/overlays/ov001/calls/ReleaseFieldPanelScreen3Widgets.c` | `void(void)`. Delegate to ReleaseOverlayWidgets. | ScriptCmd_CloseFieldPanelScreen selects this wrapper for screen selector 3. Callee destroys task +0x42c, clears it, sets bit 0 at +0x480, writes selection -2, clears layers 9/10/11 and unloads overlay 045. Limits: Selector label is operational, not an invented screen business name. All three perform the same cleanup; inherited void* result is not meaningful from a void callee. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_CloseFieldPanelScreen.c`, `eu/src/overlays/ov001/calls/ReleaseOverlayWidgets.c`. |
| ov001:0x02071d64 (Thumb) | `ReleaseFieldPanelScreen2Widgets`; `src/overlays/ov001/calls/ReleaseFieldPanelScreen2Widgets.c` | `void(void)`. Delegate to ReleaseOverlayWidgets. | ScriptCmd_CloseFieldPanelScreen selects this wrapper for screen selector 2. Callee destroys task +0x42c, clears it, sets bit 0 at +0x480, writes selection -2, clears layers 9/10/11 and unloads overlay 045. Limits: Selector label is operational, not an invented screen business name. All three perform the same cleanup; inherited void* result is not meaningful from a void callee. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_CloseFieldPanelScreen.c`, `eu/src/overlays/ov001/calls/ReleaseOverlayWidgets.c`. |
| ov001:0x02071de8 (Thumb) | `ReleaseFieldPanelScreen4Widgets`; `src/overlays/ov001/calls/ReleaseFieldPanelScreen4Widgets.c` | `void(void)`. Delegate to ReleaseOverlayWidgets. | ScriptCmd_CloseFieldPanelScreen selects this wrapper for screen selector 4. Callee destroys task +0x42c, clears it, sets bit 0 at +0x480, writes selection -2, clears layers 9/10/11 and unloads overlay 045. Limits: Selector label is operational, not an invented screen business name. All three perform the same cleanup; inherited void* result is not meaningful from a void callee. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_CloseFieldPanelScreen.c`, `eu/src/overlays/ov001/calls/ReleaseOverlayWidgets.c`. |

## Command-menu state and redraw

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x02075eec (Thumb) | `DisarmFieldMenuSelectionTags`; `src/overlays/ov001/calls/DisarmFieldMenuSelectionTags.c` | `void(void *unusedMenu, TagTracker *tracker)`. Disarm loaded tags 10/11/12/17/18 and invoke active record 0x55 callback +0x40. | UpdateFieldMenuSelectionTags performs the same disarms/callback before choosing which tag to arm; UpdateFieldMenu calls this helper when clearing pending menu area. Limits: R0 menu parameter unused; tracker is real input R1. No record destruction or invented business label for each numeric tag. Evidence sources: `eu/src/overlays/ov001/calls/UpdateFieldMenuSelectionTags.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenu.c`. |
| ov001:0x02077bcc (Thumb) | `GetFieldMenuMode`; `src/overlays/ov001/calls/GetFieldMenuMode.c` | `s32(void)`. Return menu presentation/label mode +0x68. | SetFieldMenuMode writes the exact field and chooses modeLabels surface; UpdateFieldMenu compares current/previous mode for palette update; input and gauge consumers branch on it. Limits: Distinct from list mode +0x104 and draw page +0xfc. No context check or speculative labels for every numeric mode. Evidence sources: `eu/src/overlays/ov001/calls/SetFieldMenuMode.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenu.c`, `eu/src/overlays/ov001/calls/AddGaugePoints.c`, `eu/src/overlays/ov001/calls/AdvanceMenuLevel.c`. |
| ov001:0x02078180 (Thumb) | `RedrawFieldMenuPageAndSelectionTags`; `src/overlays/ov001/calls/RedrawFieldMenuPageAndSelectionTags.c` | `void(void)`. Draw current page and refresh selection tags with list mode +0x104. | HUD layer load/unload call this around replacement/restoration. DrawMenuPanelPage uses gFieldMenuDrawHandlers; UpdateFieldMenuSelectionTags uses that list mode. Limits: No forced drawing when delegated page renderer is hidden; no new validity checks. Evidence sources: `eu/src/overlays/ov001/calls/LoadHudLayersAndRecordText.c`, `eu/src/overlays/ov001/calls/UnloadHudLayersAndRecordText.c`, `eu/src/overlays/ov001/calls/DrawMenuPanelPage.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenuSelectionTags.c`. |
| ov001:0x02078494 (Thumb) | `GetFieldMenuListMode`; `src/overlays/ov001/calls/GetFieldMenuListMode.c` | `s32(void)`. Return list mode +0x104. | SetFieldMenuMode_02078360 stores it, changes cursor/count/layout among three lists and updates tags/palettes. Command shortcuts and member-menu consumers query it. Limits: Not presentation mode +0x68. Preserve 0/1/2 without assigning unproved gameplay names. Evidence sources: `eu/src/overlays/ov001/calls/SetFieldMenuMode_02078360.c`, `eu/src/overlays/ov041/calls/HandleCommandMenuShortcuts.c`, `eu/src/overlays/ov052/calls/HandleMemberMenuInput.c`. |
| ov001:0x02078898 (Thumb) | `GetFieldMenuListMode2Cursor`; `src/overlays/ov001/calls/GetFieldMenuListMode2Cursor.c` | `s32(void)`. Return cursor +0xec when list mode +0x104 is 2, otherwise -1. | Mode-switch helper selects +0xec as active cursorIndex; HandleMemberMenuInput uses getter in its mode-2 branch. Limits: No cursor bounds check. -1 denotes wrong list mode, not an allocation result. Evidence sources: `eu/src/overlays/ov001/calls/SetFieldMenuMode_02078360.c`, `eu/src/overlays/ov052/calls/HandleMemberMenuInput.c`. |
| ov001:0x02077bd8 (Thumb) | `TryArmFieldMenuButtonDelay`; `src/overlays/ov001/calls/TryArmFieldMenuButtonDelay.c` | `BOOL(void)`. After policy guards, change negative timer +0x144 to zero if entry count +0xc8 >=2, then return true. Failed guard returns false. | UpdateFieldFlag18 enable path calls it. UpdateFieldMenu increments this timer and invokes TriggerFieldMenuButtonRecords after five updates. Limits: True permits path but does not ensure a new timer write (already armed/fewer entries). Guards are installed minigame query, mode/flag policy and lead-entry flag mask 0x80. Evidence sources: `eu/src/overlays/ov001/calls/UpdateFieldFlag18.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenu.c`, `eu/src/overlays/ov001/calls/TriggerFieldMenuButtonRecords.c`. |
| ov001:0x02077c24 (Thumb) | `TryCancelFieldMenuButtonDelay`; `src/overlays/ov001/calls/TryCancelFieldMenuButtonDelay.c` | `BOOL(void)`. After same guards, invoke active records 0x5d/0x5b/0x5c callback +0x40, set timer +0x144=-1, return true; failed guard returns false. | UpdateFieldFlag18 disable path calls it. UpdateFieldMenu consumes timer for delayed TriggerFieldMenuButtonRecords; FieldMenu_SetHidden also addresses these records. Limits: No changes after failed guards. Do not infer each callback stops or starts animation solely from slot +0x40. Evidence sources: `eu/src/overlays/ov001/calls/UpdateFieldFlag18.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenu.c`, `eu/src/overlays/ov001/calls/TriggerFieldMenuButtonRecords.c`, `eu/src/overlays/ov001/calls/FieldMenu_SetHidden.c`. |

## Round and prompt callbacks

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x02072040 (Thumb) | `InvokeFieldMinigameActiveCallback`; `src/overlays/ov001/calls/InvokeFieldMinigameActiveCallback.c` | `BOOL(void)`. If scene callback +0x134c is null, return false; otherwise normalize its result. | StartSceneMinigameTask installs IsFieldMinigameRoundActive as callbacks[3] at native +0x134c. Six-slot block also installs start/stop/input/score/level for scene IDs0xc5/0xc6/0xca. Limits: Scene work must exist. Installed callback query differs from direct minigame-field predicate; preserve null check/nonzero normalization. Evidence sources: `eu/src/overlays/ov001/calls/StartSceneMinigameTask.c`, `eu/src/overlays/ov001/calls/RunHudExitCallback.c`, `eu/src/overlays/ov001/calls/UpdateFieldMenu.c`. |
| ov001:0x0207eb04 (Thumb) | `StopFieldMinigameRound`; `src/overlays/ov001/calls/StopFieldMinigameRound.c` | `void(void)`. Hide timed arrow-prompt counters, invoke active record 0x12e callback +0x40, clear minigame active +0x20. | StartSceneMinigameTask installs callbacks[1], paired with StartFieldMinigameRound in callbacks[0]. Starter sets active to 1; input/spin updaters consume it. Limits: No task destruction or score/level reset. Owner must exist; record 0x12e purpose is not inferred beyond invoked callback. Evidence sources: `eu/src/overlays/ov001/calls/StartSceneMinigameTask.c`, `eu/src/overlays/ov001/calls/StartFieldMinigameRound.c`, `eu/src/overlays/ov001/calls/HandleListMenuConfirm.c`, `eu/src/overlays/ov001/calls/UpdateSpinningMode.c`. |
| ov001:0x0207eb98 (Thumb) | `IsFieldMinigameRoundActive`; `src/overlays/ov001/calls/IsFieldMinigameRoundActive.c` | `BOOL(void)`. True exactly when minigame work exists and active +0x20 is nonzero. | Starter sets field, stop callback clears it; StartSceneMinigameTask installs this direct predicate at scene +0x134c. Limits: No task allocation/advancement. Distinct from indirect callback invoker. Evidence sources: `eu/src/overlays/ov001/calls/StartSceneMinigameTask.c`, `eu/src/overlays/ov001/calls/StartFieldMinigameRound.c`, `eu/src/overlays/ov001/calls/HandleListMenuConfirm.c`, `eu/src/overlays/ov001/calls/UpdateSpinningMode.c`. |
| ov001:0x0207e26c (Thumb) | `RandomizePositiveSpinPrompt`; `src/overlays/ov001/calls/RandomizePositiveSpinPrompt.c` | `void(FieldMinigame *game, BOOL bindSprites)`. Randomize binary-angle +0x24 to a quarter turn; store signed direction+1 at +0x26, step scale 0x400 at +0x28; optionally bind shared HUD sprite slots. | InitContextForMode selects it for mode 2 and starter reuses with binding false. UpdateSpinningMode adds direction*step modulo0x10000; HandleDirectionalPrompt maps angle sectors to input. Limits: Positive means arithmetic increment, without asserting clockwise screen orientation. Mode 3 counterpart RandomizeFacing writes direction-1. No binding when second arg zero. Evidence sources: `eu/src/overlays/ov001/calls/InitContextForMode.c`, `eu/src/overlays/ov001/calls/StartFieldMinigameRound.c`, `eu/src/overlays/ov001/calls/UpdateSpinningMode.c`, `eu/src/overlays/ov001/calls/HandleDirectionalPrompt.c`, `eu/src/overlays/ov001/calls/BindHudNodeOffsets.c`, `eu/src/overlays/ov001/calls/RandomizeFacing.c`. |

## Entry-pool dispatch, flags and counts

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x020863f4 (Thumb) | `QueryEntryPoolMotionVector`; `src/overlays/ov001/calls/QueryEntryPoolMotionVector.c` | `u32(EntryPoolObject *entry, VecFx32 *out)`. If owner op +0x20 exists, return its raw(entry,out) result; otherwise zero. | Pool constructors install actor-velocity backends or vertical-three-word backends. ApplyLinkedObjectMotion consumes output as motion delta. Limits: No entry/availability/flag check, output initialization or result normalization. No uniform absolute-position, handle or velocity-unit assertion across backend kinds. Evidence sources: `eu/src/overlays/ov016/calls/CreateFieldUnit.c`, `eu/src/overlays/ov016/calls/GetFieldUnitVelocity.c`, `eu/src/overlays/ov017/calls/CreateKind4EntryPool.c`, `eu/src/overlays/ov019/calls/TryGetExtraDataHandle.c`, `eu/src/overlays/ov020/calls/TryGetFieldHandle.c`, `eu/src/overlays/ov052/calls/ApplyLinkedObjectMotion.c`. |
| ov001:0x02086408 (Thumb) | `DispatchEntryPoolHitMessage`; `src/overlays/ov001/calls/DispatchEntryPoolHitMessage.c` | `u32(EntryPoolObject *entry, void *message)`. If owner op +0x1c exists, return raw(entry,message) result; otherwise zero. | Constructors install HandleFieldObjectHit_020a50a4, HandleFieldObjectActivation and FieldObject_TakeDamage; actor/projectile hit consumers use dispatcher. Limits: No entry/active flag guard or output normalization. Backend returns status/bit values; no uniform accept/reject interpretation of zero/nonzero. Evidence sources: `eu/src/overlays/ov016/calls/CreateFieldUnit.c`, `eu/src/overlays/ov017/calls/CreateKind4EntryPool.c`, `eu/src/overlays/ov017/calls/HandleFieldObjectActivation.c`, `eu/src/overlays/ov018/calls/CreateKind6EntryPool.c`, `eu/src/overlays/ov059/calls/Actor_UpdateSweepHits.c`. |
| ov001:0x0208641c (Thumb) | `GetEntryPoolTargetPosition`; `src/overlays/ov001/calls/GetEntryPoolTargetPosition.c` | `const VecFx32 *(EntryPoolObject *entry)`. Require entry flag mask 0x08, then return op +0x28 result if present; otherwise null. | Constructors install raised/top/focus-position backends. Wait-target, approach-choice and nearby-object consumers use the borrowed vector. Limits: Does not check IsNodeFlagBitClear. Backend-owned pointer may reference shared scratch; no allocation/lifetime extension. Evidence sources: `eu/src/overlays/ov016/calls/CreateFieldUnit.c`, `eu/src/overlays/ov016/calls/GetFieldUnitTopPosition.c`, `eu/src/overlays/ov017/calls/GetOwnerRaisedPosition.c`, `eu/src/overlays/ov001/calls/GetWaitTargetPosition.c`, `eu/src/overlays/ov052/calls/BuildApproachChoices.c`, `eu/src/overlays/ov058/calls/PurgeNearbyStageObjects.c`. |
| ov001:0x0208643c (Thumb) | `GetEntryPoolTargetRangeFx12`; `src/overlays/ov001/calls/GetEntryPoolTargetRangeFx12.c` | `fx32(EntryPoolObject *entry)`. Return -1 unless IsNodeFlagBitClear and entry flag mask 0x08; otherwise return owner word +0x44. | Constructors set range +0x44=0x3000. IsEntryWithinFacingRange clamps maximum against it and uses it in axis/distance tests. Limits: Preserve sentinel and raw FX12 value. This is range cap, not the id of an inherited partial struct; no null check. Evidence sources: `eu/src/overlays/ov001/calls/IsEntryWithinFacingRange.c`, `eu/src/overlays/ov001/calls/IsNodeFlagBitClear.c`, `eu/src/overlays/ov016/calls/CreateFieldUnit.c`, `eu/src/overlays/ov017/calls/CreateKind4EntryPool.c`, `eu/src/overlays/ov020/calls/CreatePanelEntryPool.c`. |
| ov001:0x02087058 (Thumb) | `SetEntryPoolUpdatesBlocked`; `src/overlays/ov001/calls/SetEntryPoolUpdatesBlocked.c` | `void(BOOL blocked)`. Nonzero sets manager bits 0x01/0x80; zero clears only0x01. | UpdateEffectManager resets linked-actor offsets for 0x80, clears it, then suppresses updates for mask 0x51 including0x01; SetOverlayLayerVisible forwards input. Limits: Actual update blocking differs from caller visible label. Clearing does not cancel pending reset or alter independent interaction/draw rules. Evidence sources: `eu/src/overlays/ov001/calls/UpdateEffectManager.c`, `eu/src/overlays/ov001/calls/ResetLinkedActorOffsets.c`, `eu/src/overlays/ov001/calls/SetOverlayLayerVisible.c`. |
| ov001:0x0208707c (Thumb) | `SetEntryPoolConditionalUpdatePause`; `src/overlays/ov001/calls/SetEntryPoolConditionalUpdatePause.c` | `void(BOOL paused)`. Nonzero sets0x40/0x80; zero clears only0x40. | SelectNextSessionState enables pause. UpdateEffectManager suppresses update under 0x51, clears0x40 once IsFirstEntryFlagSet false; that helper tests lead-entry flag mask 0x10, defaults true without context. Limits: Distinct from explicitbit0 and cachebit0x10 pause.0x80 queues reset even if pause clears; no gameplay label for lead mask 0x10. Evidence sources: `eu/src/overlays/ov001/calls/SelectNextSessionState.c`, `eu/src/overlays/ov001/calls/UpdateEffectManager.c`, `eu/src/overlays/ov001/calls/IsFirstEntryFlagSet.c`, `eu/src/overlays/ov001/calls/ResetLinkedActorOffsets.c`. |
| ov001:0x020871a0 (Thumb) | `RequestFieldEntryResourceDelivery`; `src/overlays/ov001/calls/RequestFieldEntryResourceDelivery.c` | `void(void)`. If queued-resource bit 0x02 set, set load/deliverybits0x04/0x08. | ReallocTableEntry initializes requested slots and sets0x02. StepResourceSlotLoading consumes0x04/0x08, loads pairs, notifies listeners, frees temporary file and marks each entry delivered. Limits: No immediate callback/result or all-resources-ready guarantee. Loader can return false after one delivery. Distinguish global flags from per-entry flags. Evidence sources: `eu/src/overlays/ov001/calls/ReallocTableEntry.c`, `eu/src/overlays/ov001/calls/StepResourceSlotLoading.c`, `eu/src/overlays/ov001/calls/ResourceCache_Shutdown.c`. |
| ov001:0x02087270 (Thumb) | `GetFieldEntryPoolCount_02087270`; `src/overlays/ov001/calls/GetFieldEntryPoolCount_02087270.c` | `s32(void)`. Return signed byte count at manager +0x04. | DestroyAllEffectEntries loops this count over pool-pointer array+0 and clears it. FindKind4FieldObject and InitAreaRewardScene use getter as GetFieldEntryPoolAtIndex bound. Limits: Equivalent getter already exists at 0208722c as GetFieldEntryPoolCount; retain address suffix rather than invent distinct semantics. Not area ID; preserve signed extension, no owner-null check. Evidence sources: `eu/src/overlays/ov001/calls/DestroyAllEffectEntries.c`, `eu/src/overlays/ov001/calls/GetFieldEntryPoolAtIndex.c`, `eu/src/overlays/ov001/calls/GetFieldEntryPoolCount.c`, `eu/src/overlays/ov017/calls/FindKind4FieldObject.c`, `eu/src/overlays/ov040/calls/InitAreaRewardScene.c`. |
| ov001:0x02087644 (Thumb) | `GetActiveFieldEntryListCount`; `src/overlays/ov001/calls/GetActiveFieldEntryListCount.c` | `u16(void)`. Return active-list count halfword +0x06. | AppendNodeToActiveList links node and increments count; StopAndClearFieldEntryList clears count and links; map renderer uses it to size overflow storage. Limits: Distinct from signed pool count +0x04. Count includes linked entries before renderer filtering. No owner-null check. Evidence sources: `eu/src/overlays/ov001/calls/AppendNodeToActiveList.c`, `eu/src/overlays/ov001/calls/StopAndClearFieldEntryList.c`, `eu/src/overlays/ov023/calls/UpdateMapObjectIcons.c`. |

## Mode reward tables and request layout

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x02086950 (Thumb) | `GetModeEntryUnlockRewardRecord`; `src/overlays/ov001/calls/GetModeEntryUnlockRewardRecord.c` | `RewardEntry *(int index)`. Return six-byte record +0x1c4+index*6 when index<signed count +0x1c0, else null. | ResourceCache_LoadModeTables copies six-byte records from slot 6 for GetCtxModeByte; GrantEntryUnlockReward reads reward IDs and low/high bytes for spawn/drop. Limits: No lower-bound, owner or buffer check. Borrowed pointer, no grant or ownership transfer. Evidence sources: `eu/src/overlays/ov001/calls/ResourceCache_LoadModeTables.c`, `eu/src/overlays/ov001/calls/GrantEntryUnlockReward.c`. |
| ov001:0x02086974 (Thumb) | `GetModeEntryUnlockRewardId`; `src/overlays/ov001/calls/GetModeEntryUnlockRewardId.c` | `s16 *(int index)`. Return signed-halfword element +0x1bc+index*2 when index<signed count +0x1b8, else null. | Mode-table loader copies slot 6 IDs. GrantEntryUnlockReward tests pointed ID against-1 before reward-spawn/item-drop operations. Limits: Pointer return, not ID value. No negative-index or manager checks. Owned until table release. Evidence sources: `eu/src/overlays/ov001/calls/ResourceCache_LoadModeTables.c`, `eu/src/overlays/ov001/calls/GrantEntryUnlockReward.c`. |
| ov001:0x0208743c (Thumb) | `ReleaseFieldEntryRewardTables`; `src/overlays/ov001/calls/ReleaseFieldEntryRewardTables.c` | `void(void)`. Free nonnull arrays +0x1bc/+0x1c4 and clear pointers. | Mode-table loader allocates the halfword/six-byte reward arrays consumed by GrantEntryUnlockReward; DestroyFieldObjectManager calls cleanup. Limits: Counts +0x1b8/+0x1c0 remain; no manager free. Preserve call order preventing stale-count access. Evidence sources: `eu/src/overlays/ov001/calls/ResourceCache_LoadModeTables.c`, `eu/src/overlays/ov001/calls/GrantEntryUnlockReward.c`, `eu/src/overlays/ov001/calls/DestroyFieldObjectManager.c`. |
| ov001:0x020874f4 (Thumb) | `InitEntryUnlockRewardRequest`; `src/overlays/ov001/calls/InitEntryUnlockRewardRequest.c` | `void(UnlockRequest *request, u32 mode, u32 entry, s32 dropOnUnlock, s32 dropOnLock, u32 flagEntry, u32 flagSlot)`. Store [mode,entry,dropOnLock,dropOnUnlock,flagEntry,flagSlot] as six words, exchanging incoming third/fourth payload positions. | GrantEntryUnlockReward reads exact 24-byte layout. DropRequest_InitKind0/1 and GrantFieldObjectReward prepare it for that consumer. Limits: No further initialization/validation. Preserve different drop branches; mode consumed as skipModeCheck, not invented kind enum. Evidence sources: `eu/src/overlays/ov001/calls/GrantEntryUnlockReward.c`, `eu/src/overlays/ov001/calls/DropRequest_InitKind0.c`, `eu/src/overlays/ov016/calls/GrantFieldObjectReward.c`. |

## Registered collision/contact predicates

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x02084604 (Thumb) | `FilterPatrolMoveSurface`; `src/overlays/ov001/calls/FilterPatrolMoveSurface.c` | `BOOL(CollisionRecord *record, PatrolObject *object)`. Accept by default; in non-kind 4/negative-slot/kind 1-match case reject matching routed group-slot/world-entry discriminator. | UpdatePatrolMove installs it as movement and ground-sweep surface filter. It traverses record payload/current group slot, rather than object animation state. Limits: Preserve kind checks, -1-slot encoding, four-ID scan and0xff sentinel. No new fallback/bounds validation if no scanned ID matches. Evidence sources: `eu/src/overlays/ov001/calls/UpdatePatrolMove.c`. |
| ov001:0x020847ec (Thumb) | `FilterShadowGroundSurface`; `src/overlays/ov001/calls/FilterShadowGroundSurface.c` | `BOOL(CollisionRecord *record)`. Accept except kind 4 records with owner +0x6c discriminator1,0x15,0x17..0x19. | SweepShadowToGround installs callback with actor context; native body only reads R0 record, bound actor context unused. Limits: Do not name owner +0x6c a state or actorID without writer proof. Only filter predicate; actual swept collision/output belongs to SweepWorldCollision. Evidence sources: `eu/src/overlays/ov001/calls/SweepShadowToGround.c`. |
| ov001:0x020825c8 (Thumb) | `FilterFieldSwitchTouchContact`; `src/overlays/ov001/calls/FilterFieldSwitchTouchContact.c` | `BOOL(void *unusedContext, CollisionRecord *record)`. True only for nonnull record, kind 2 and zero owner word+4. | ActivateFieldSwitchObject installs touch callback/context pair; native function consumes R1 record, not R0 context. Limits: No mutation; kind/zero discriminator remain numeric, without primary-player/all-actor claim. Preserve R1 real input despite erased one-argument callback registration. Evidence sources: `eu/src/overlays/ov001/calls/ActivateFieldSwitchObject.c`. |
| ov001:0x02083334 (Thumb) | `FilterCapsuleFieldObjectContact`; `src/overlays/ov001/calls/FilterCapsuleFieldObjectContact.c` | `BOOL(void *unusedContext, CollisionRecord *record)`. True only for nonnull record with kind word+4=0x15. | RespawnCapsuleFieldObject installs contact predicate and calls SetActorExtraPosition(...,0x15), tying discriminator to capsule-contact family. Limits: Tested input R1, context R0 unused. No general damage/activation/intersection meaning for this tag filter. Evidence sources: `eu/src/overlays/ov001/calls/RespawnCapsuleFieldObject.c`. |

## Class-manager flags, shadow and cleanup

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and limits |
|---|---|---|---|
| ov001:0x0207f0c0 (Thumb) | `GetFieldObjectShadowModel`; `src/overlays/ov001/calls/GetFieldObjectShadowModel.c` | `SceneNode *(void)`. Return borrowed shadow scene-node pointer +0x11c. | ObjectManager_LoadShadowModel allocates/initializes mo/sd resource and alpha8. DrawLinkedActorPass sets translation/radius scale then draws it for non-volume shadows. Limits: No owner-null check or transfer. Resource reset releases/detaches, frees and clears node; callers cannot retain afterward. Evidence sources: `eu/src/overlays/ov001/calls/ObjectManager_LoadShadowModel.c`, `eu/src/overlays/ov001/calls/DrawLinkedActorPass.c`. |
| ov001:0x0207f078 (Thumb) | `ObjectManager_SetFlagBit`; `src/overlays/ov001/calls/ObjectManager_SetFlagBit.c` | `void(u32 bitIndex)`. Delegate bit-index setting on manager field +0x120. | ObjectManager_IsFlagBitSet reads identical field via GetPackedBitMask; class loaders set indices before later tests. Resource reset clears word. Limits: Bit index, not shifted mask. No new bounds check or guessed per-feature meaning. Manager must exist. Evidence sources: `eu/src/overlays/ov001/calls/ObjectManager_IsFlagBitSet.c`, `eu/src/overlays/ov020/calls/LoadPanelStackPhase.c`, `eu/src/overlays/ov020/calls/LoadStackedBlockPhase.c`. |
| ov001:0x0207efa0 (Thumb) | `ResetFieldObjectManagerResources`; `src/overlays/ov001/calls/ResetFieldObjectManagerResources.c` | `void(void)`. Release linked class objects, clear +0x120 bitfield, release/detach/free optional shadow node +0x11c, then release entry-pool effects/resources. | DestroyListNodes walks objects through ReleaseObjectUse. Shadow loader is paired constructor. Native 0x0207efba passes shadow node in R0 to ReleaseResourceAndDetach, although C declaration erases argument. Limits: No outer class-manager/archive free. Native R0 is a real resource input; this name-only block does not repair declaration. Evidence sources: `eu/src/overlays/ov001/calls/DestroyListNodes.c`, `eu/src/overlays/ov001/calls/ObjectManager_LoadShadowModel.c`, `eu/src/overlays/ov001/calls/ReleaseEffectResources.c`, `eu/src/calls/ReleaseResourceAndDetach.c`. |

## Remaining evidence boundaries

Collision callbacks are named for the actual installed operation: patrol
movement surface filtering, shadow-ground filtering, switch touch and capsule
contact. Numeric record kinds and owner discriminators are specified per row.
No unproved player identity, actor-state enumeration, damage result or geometry
intersection result is assigned to a tag predicate. Preserve the real input
registers where old one-argument callback types erased an R1 record input.

Native object offsets, pointer ownership, unchecked lower bounds, signed
extension, FX12 quantities, binary angles, per-backend result values, callback
null handling and shared-window phases require separate attention in a port.
This block renames functions; it does not silently repair those ABI/layout
boundaries or add validation that would change the original behavior.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldHudTextResources.c ReleaseFieldHudTextResources --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldMessageLineWindow.c ReleaseFieldMessageLineWindow --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldRecordNamesAndEntryList.c ReleaseFieldRecordNamesAndEntryList --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSceneTextWindow4D8.c ReleaseSceneTextWindow4D8 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSceneTextWindow51C.c ReleaseSceneTextWindow51C --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldChoiceWindow.c ReleaseFieldChoiceWindow --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSlotLabelWindowsAndMessages.c ReleaseSlotLabelWindowsAndMessages --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldHudGaugeRange.c SetFieldHudGaugeRange --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldPanelScreen3Widgets.c ReleaseFieldPanelScreen3Widgets --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldPanelScreen2Widgets.c ReleaseFieldPanelScreen2Widgets --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldPanelScreen4Widgets.c ReleaseFieldPanelScreen4Widgets --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldHudBottomRowEnabled.c SetFieldHudBottomRowEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldSceneEntryListRecord.c GetFieldSceneEntryListRecord --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldSceneLocationName.c GetFieldSceneLocationName --thumb
python tools/verify_idx.py src/overlays/ov001/calls/BlitGaugeFillPattern.c BlitGaugeFillPattern --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DisarmFieldMenuSelectionTags.c DisarmFieldMenuSelectionTags --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldMenuMode.c GetFieldMenuMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RedrawFieldMenuPageAndSelectionTags.c RedrawFieldMenuPageAndSelectionTags --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldMenuListMode.c GetFieldMenuListMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldMenuListMode2Cursor.c GetFieldMenuListMode2Cursor --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryArmFieldMenuButtonDelay.c TryArmFieldMenuButtonDelay --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryCancelFieldMenuButtonDelay.c TryCancelFieldMenuButtonDelay --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InvokeFieldMinigameActiveCallback.c InvokeFieldMinigameActiveCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StopFieldMinigameRound.c StopFieldMinigameRound --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsFieldMinigameRoundActive.c IsFieldMinigameRoundActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RandomizePositiveSpinPrompt.c RandomizePositiveSpinPrompt --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueryEntryPoolMotionVector.c QueryEntryPoolMotionVector --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DispatchEntryPoolHitMessage.c DispatchEntryPoolHitMessage --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetEntryPoolTargetPosition.c GetEntryPoolTargetPosition --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetEntryPoolTargetRangeFx12.c GetEntryPoolTargetRangeFx12 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetModeEntryUnlockRewardRecord.c GetModeEntryUnlockRewardRecord --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetModeEntryUnlockRewardId.c GetModeEntryUnlockRewardId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetEntryPoolUpdatesBlocked.c SetEntryPoolUpdatesBlocked --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetEntryPoolConditionalUpdatePause.c SetEntryPoolConditionalUpdatePause --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestFieldEntryResourceDelivery.c RequestFieldEntryResourceDelivery --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldEntryPoolCount_02087270.c GetFieldEntryPoolCount_02087270 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldEntryRewardTables.c ReleaseFieldEntryRewardTables --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitEntryUnlockRewardRequest.c InitEntryUnlockRewardRequest --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetActiveFieldEntryListCount.c GetActiveFieldEntryListCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FilterPatrolMoveSurface.c FilterPatrolMoveSurface --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FilterShadowGroundSurface.c FilterShadowGroundSurface --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FilterFieldSwitchTouchContact.c FilterFieldSwitchTouchContact --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FilterCapsuleFieldObjectContact.c FilterCapsuleFieldObjectContact --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldObjectShadowModel.c GetFieldObjectShadowModel --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ObjectManager_SetFlagBit.c ObjectManager_SetFlagBit --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetFieldObjectManagerResources.c ResetFieldObjectManagerResources --thumb
bash tools/gate.sh
```
