# Menu callbacks, popup tasks and registered empty handlers

This block names 80 EU entrypoints by their bodies, descriptor slots and callers. The tables preserve separate overlay identities even when small functions have identical bytes. An address such as `0x020beae0` identifies different data in overlays 090 and 092; the bank is part of the identity.

This document describes partial native layouts and observed call protocols for a later port. It does not recover complete screen classes or assign gameplay meanings to opaque states. The source tables use the accepted names and paths for this block; source paths in those tables are relative to `eu/`. Supporting shared-source paths elsewhere are relative to the repository root. The validation section records the official checks for this naming block.

## Descriptor ownership and lifetime

Overlay 039 owns the primary/secondary menu lifecycle. Its ROM registry records are eight-byte pairs `{overlayId, descriptorPointer}`. The primary table starts at `ov039:0x020be94c` (19 records); the secondary table at `ov039:0x020be8ec` (12 records). Pointer values must be resolved in the selected overlay, not the default RAM space.

| Descriptor | +0x00 | +0x04 | +0x08 | +0x0c | +0x10 | Input callbacks |
|---|---|---|---|---|---|---|
| Primary | Init callback | Destroy callback | Update callback | Secondary registry index | Work size | Begin at +0x14 |
| Secondary | Init callback | Destroy callback | Update callback | Work size | First input callback | Begin at +0x10 |

These prefixes differ by one word. In particular, primary +0x0c is not a work size. `LoadSecondarySubOverlay`, `CloseSecondarySubOverlay`, `UpdateSubOverlayHandlers` and the dispatchers in `src/ov039/overlay_handling/` and `src/ov039/menu_dispatch/` establish the slot meanings. EU aliases in `eu/src/overlays/ov039/calls/` map the shared sources to their native addresses. The active primary work and secondary work are separate pointers at runtime state +0xc998 and +0xc99c.

The seven placeholder secondary descriptors all start at `0x020beae0` in their respective banks. Their work size is four bytes. Their initializer returns literal 1, which the overlay039 lifecycle stores as secondary readiness at `ov039:0x020bb238`; it does not initialize those four bytes. Their destroy and update functions are `BX LR` with no memory effects. The runtime owns their work allocation. Keep the callbacks and descriptors distinct; do not infer a particular report-page purpose from their adjacent overlay numbers.

| Secondary registry index | Overlay | Descriptor | Init / destroy / update addresses |
|---|---|---|---|
| 4 | 090 | `ov090:0x020beae0` | `0x020beac0` / `0x020beac8` / `0x020beacc` |
| 5 | 092 | `ov092:0x020beae0` | Same offsets in ov092 |
| 6 | 094 | `ov094:0x020beae0` | Same offsets in ov094 |
| 7 | 096 | `ov096:0x020beae0` | Same offsets in ov096 |
| 8 | 098 | `ov098:0x020beae0` | Same offsets in ov098 |
| 9 | 100 | `ov100:0x020beae0` | Same offsets in ov100 |
| 10 | 102 | `ov102:0x020beae0` | Same offsets in ov102 |

The descriptor in ov088 at `0x020bee80` instead has 64-byte work for its caption layer. Its empty update slot is separately named `UpdateOverlay088CaptionLayerNoop`. The empty primary update in ov078 is at descriptor `ov078:0x020c4fe0` +0x08; primary registry index 4 selects it. Input callbacks in later slots remain active.

## Return protocols and callback presence

An empty body does not supply a universal return contract. In ARM/Thumb, `BX LR` leaves the incoming `r0` unchanged. This may be a work pointer, a window pointer, or even a callback address, depending on the dispatch sequence. It is not evidence of a newly owned object or a success BOOL.

| Family | Machine result and observed consumer |
|---|---|
| Placeholder secondary init | Literal 1 is consumed as readiness. |
| Placeholder secondary destroy | Residual work pointer is discarded: the close path loads `r0 = 0` before unloading. |
| Placeholder/ov088 secondary update | The secondary dispatcher at `ov039:0x020bd074` propagates residual `r0`. Audited outer frame paths overwrite it; one initialization path propagates it through another state dispatcher before the frame caller overwrites it. |
| Ov078 primary update | The primary dispatcher propagates residual `r0`; all eight audited runtime callsites overwrite it before use. The function is an update hook, not an input test. |
| Status overview input update | Computes literal 0. Its real consumer compares the result and continues global tab navigation on zero. |
| Save-select L/R input callbacks | Callback residual `r0` is discarded; the invoker returns 1 because the callback pointer is present. |
| Selection-panel state-entry hooks | `EnterPanelState` propagates the scene pointer. For states 8/9, `PushPanelState` overwrites it; `PopPanelState` overwrites it on all audited paths. |
| Report scene and popup-window empty state handlers | Audited frame callers overwrite the residual register and continue common work. The StoryReport scene dispatcher uses `BLX r0`, so its empty hook retains the callback address rather than a scene pointer. |
| Matrix cursor and embedded-substate empty hooks | Their direct callers overwrite residual `r0` before any use. |

The save-select handlers demonstrate why callback presence matters. Primary descriptor `ov080:0x020c5da0` contains the L callback at +0x34 and the R callback at +0x38. `PollHandlerInput` tests masks `0x200` and `0x100`. The paired dispatchers try primary input before secondary input. `InvokeIfPresent`, at EU `ov039:0x020bcdb8`, calls a non-NULL callback and then executes `MOV r0,#1` regardless of the callback's result. Thus each registered empty handler consumes that button, suppresses the secondary fallback and stops later polling. Replacing its pointer with NULL changes behavior.

The evidence is the descriptor data (`src/ov080/data/Data_ov080_020c5d80.c`, EU aliases/ROM above), `src/ov039/input/PollHandlerInput_020baf1c.c`, `src/ov039/menu_dispatch/dispatchMenuHandlerPairAt34_020bd444.c` and `src/ov039/input/dispatch_input_handler_pair_38_020bd4bc.c`. Source suffixes in the shared files retain their reference-region addresses; the explicit ROM addresses here are EU.

For the primary update, the eight EU caller addresses are `ov039:0x020bb1d8`, `0x020bb2e8`, `0x020bb344`, `0x020bb374`, `0x020bb444`, `0x020bb4e0`, `0x020bb530` and `0x020bb6b8`. The status overview has a distinct consumed zero at `ov073:0x020bf6f0` (`BLX`) followed by the compare at `0x020bf6f2`. Do not turn either family into the other's BOOL protocol.

## Confirmation, redraw and selection operations

The item picker, slot menu and item screen are separate owners with parallel callback bodies. Their confirmation-open wrappers install three callback/context pairs and return literal 1. The ordered callbacks are the mutation worker, a header/restoration helper and an input-disable helper. Existing local names such as `onUpdate/onEnter/onExit` do not establish a general lifecycle protocol for these slots.

`OpenItemPicker` and `ItemList_OpenConfirmWindow` store the three eight-byte pairs from work +0x11be0, each using the caller's menu work as context. The slot opener also closes its underlying item list, marks the confirmation window open, saves the BG1 color mode, switches that mode, and preserves 0x680 bytes of screen backup. See `src/ov075/unclassified_helpers/OpenItemPicker_020ce9ac.c` and `src/ov076/unclassified_helpers/ItemList_OpenConfirmWindow_020ca7bc.c`, through their EU wrappers. The documented offset is a partial owner view, not a shared whole-menu struct for all overlays.

`ConsumeItemPickerSelectionAndApplyReward` applies the selected reward when the selection is not locked, updates stock/accounting including the equipped-slot case, and then sets state 4/redraw even if no reward was applied. Preserve the source's slot-search assumptions: it has no new not-found recovery branch. The slot-menu reward worker's old `ItemList_ReturnCursorItem` label refers to applying a reward/decrementing stock, not to a menu Back action. Its discard worker releases/clears the selection only when `keepEntry` is false. These workers are evidence for the new confirmation names; no worker algorithm is changed in this block.

`ClearSlotMenuBg1AndRedrawSelection` and `ClearItemScreenBg1AndRedrawList` clear 0x5040 bytes of BG1 character memory. They restore the saved color mode while preserving other control fields, reset a word at +4, and bracket their respective panel-open call with a redraw guard set to 1 and then 0. They return TRUE. This is not a promise to clear the tilemap or restore every display register. The two entrypoints remain separate because their panel-open callees and work owners differ.

The three `Is...PartyHpFull` predicates compare each active participant record's unsigned current HP at +2 with its maximum HP at +4. They return FALSE for `current < maximum`, so a value above maximum also passes; zero participants returns TRUE. They do not clamp values or validate the participant count. This field interpretation is supported by `src/arm9/overlay_selection/SetupAllSelectionRecords_0204f85c.c` passing the same record to `ComputePlayerStats`, the HP calculation in `src/arm9/unclassified_helpers/ComputePlayerStats_02050b30.c`, and `src/arm9/overlay_selection/ApplySelectionStatScaling_0204fbcc.c`, which preserves current HP, scales maximum HP and clamps the preserved value. These fields are not item-stock counts or the separate opaque session words at +0x27a8/+0x27ac/+0x27b0.

`SelectPreviousMenuPage` counts the packed flags at `0x9f7 + 2*category` plus `0xa01 + category`. It only decrements when that count is nonzero; page zero wraps to the last page only while input mask 0x40 is held. Sound/tab/header work occurs only on a page change. The category's gameplay meaning is not recovered here.

The four ov089 callbacks operate on the active menu scene and its popup selection, not a TaskObject popup owner. Directional cursor movement requires confirm mode and input mask 0xf0; the event passed to `MoveCursorToElement` is a widget/element ID. `ConfirmOrClosePopup` honors its blocked guard, closes an existing popup when work +0x904 is nonzero, otherwise sounds and enables confirmation mode. `ResetPopupConfirmModeWithSound` sounds before disabling that mode. `CommitPopupSelectionToSessionBits` encodes a selected record ID as 7 when negative or equal to 8, otherwise as ID+1; it writes the three-bit packed field at 0x3703, sounds, and requests subscene closure. Preserve this exact encoding/narrowing; no bounds recovery or gameplay name for the packed field is established.

The theater callback is named `CommitTheaterEntrySelection` because it gates on phase 3 and availability set 0, stores the selected ID through `RuntimeState_SetObjectId`, and closes the subscene. It neither unlocks an entry nor directly opens/plays a movie. `RefreshUnlockedEntries` and `IsEntryFlagSet` in `src/ov103/panel_state/` establish availability-set population and lookup; their legacy names are not proof of an unlock action in this callback. The commit sound precedes storing the ID. `CancelTheaterEntrySelection` stores -1 and requests closure before its cancel sound. Neither callback adds a selection-bounds guard.

`CloseOverlay078Menu` sounds, pops the menu stack and requests `StartSubScene(0,-1,0)`. The superficially similar ov081 close entrypoint uses a different third argument and is outside this 80-function block; do not merge the two by appearance.

## Popup task, work and window boundaries

The ReportTop and Trophy popup implementations have separate globals and lifetimes. The task handle, task work allocation and embedded popup window are three different objects.

| Native view | Established storage | Boundaries |
|---|---|---|
| ReportTop popup work | Global `data_ov091_020c375c`; task handle at +0; four initializer words at +4/+8/+0xc/+0x10; loaded background resource +0x1c and background view +0x20. | The font use at +8 is established by `DrawPopupText`. A work pointer is not its task handle. |
| Trophy popup work | Global `data_ov093_020c5104`; corresponding partial window/queue views. | Do not infer its complete allocation size solely from the ReportTop descriptor. |
| Embedded PopupWindow | Work +0x2c; signed state at window +0, flags +4, timer +8. | These fields are separate from the outer report-scene state and from the queue count. |
| Popup queue | Work +0x8c; 30 entries of 16 bytes: signed x/y, UTF-16 text pointer, final signed parameter. Count at work +0x26c. | The producer has no capacity guard. The fourth parameter's full UI meaning is not reconstructed here. |

ReportTop's task descriptor is at `ov091:0x020c2c94` (the data view at `0x020c2c88` plus 0x0c). It names constructor `0x020c1878`, destructor `0x020c1930` and work size 0x270. The 20-byte descriptor, 44-byte TaskObject and 0x270-byte work allocation are separate native objects. `ReportTopPopup_InitTaskWork` obtains work through `GetRunningTaskWork`, publishes its global, copies the four initializer words, clears the background-resource field and queue count, loads background entry 3, and returns the `UpdatePopupManager` code pointer. It does not return a newly allocated work pointer.

`ReportTopPopup_CreateTask` calls `CreateTaskObject` with that descriptor and the initializer argument, stores the returned task handle at work +0, and returns that handle. The registered destructor frees the background and clears the work global; the task system owns the task/work teardown. The two `DestroyTask` wrappers take the task handle expected by the task API. Do not reinterpret residual/tail-call `r0` as a new allocation or substitute an embedded window pointer.

The flag helpers operate on a supplied PopupWindow: OR mask, AND-NOT mask, or return raw `flags & mask`. The last is not a normalized BOOL. Only mask 1's text-initialized guard is established by `DrawPopupText` and `ClosePopupText`; it does not prove complete resource ownership, and the NULL-text release path skips text-layer destruction. The setter/clearer machine bodies leave the input address in `r0`; this does not establish a fluent host API.

`GetState` returns the signed state word. `GetCurrentState` reads the live global's embedded window and returns that state; the original generated C's void-like declaration is not evidence that the result is unused. Callers compare the result. These accessors have no NULL/lifetime guard and must be used while the popup task is alive.

The two `QueueMessage` wrappers forward four logical inputs `(x, y, text, parameter)` despite an old zero-argument library template. `QueuePopupMessage`/`QueuePopup` copies non-NULL UTF-16 text to an allocated `(length+1)*2` buffer and terminates it. The caller's text is borrowed for that synchronous copy; the queued copy is owned until the popup processing/release path disposes of it. A NULL text argument does not clear the slot's previous text pointer. The producer increments queue count without checking capacity. No new returned-pointer ownership contract follows from the wrapper's tail-call register value.

Evidence is in `eu/src/overlays/ov091/calls/QueuePopupMessage.c`, `eu/src/overlays/ov093/calls/QueuePopup.c`, the two `DrawPopupText`/`ClosePopupText` call families, `src/ov091/panel_state/UpdatePopupManager_020c194c.c`, and the corresponding ov093 worker. The TaskObject/work distinction is also documented in `eu/docs/TASK_INPUT_VM_HELPERS.md`.

## Registered empty hooks within live screens

The report-scene state tables register separate outer state-0 handlers in ov091/093/095/097/099/101, plus the distinct Trophy state-6 handler. Empty means no state-specific body effect, not a frozen frame or an inferred idle state: common rendering, captions and cursor work continue around the call. State numbers remain numerical where no stronger role is proven.

The ReportTop popup-window state-0 table slot is at `ov091:0x020c2a10`; Trophy's is at `ov093:0x020c3e74`. They pass work +0x2c to the hook. `UpdatePopupManager` subsequently reads queue count and may start a queued popup, then returns literal 0. Its empty state hook is distinct from `ReportTop_HandleState0Noop` for the outer screen.

The SelectionPanel state table has 18 state-entry slots. Slots 8/9 call `(scene, previousState)` through `EnterPanelState` after common widget/slot setup. They are entry hooks, not per-frame updates. Retain their state numbers and the surrounding common setup.

The Matrix cursor table at `ov075:0x020d1428` contains five Thumb callback words. Indices 0, 1 and 4 install the empty callbacks for pages 1, 2 and 5 because `OpenPage` stores `page=index+1`. The installed pointer is menu +0x13ea8; the frame call at `ov075:0x020c6c6a` is followed immediately by an `LDR r0` at 0x020c6c6c. Preserve the table ordering and separate callback identities; no gameplay labels for those page ordinals are inferred.

The three `Destroy...SubstateNoop` callbacks receive embedded work +0x34 during their parent's teardown, after model release at +0x6f4 and before layout destruction. Their direct callers then restore the parent in `r0`. The substate's full role is unresolved; an existing private `listState` label does not prove a list/widget class or a resource-free operation inside the empty body. `ItemScreen_HandleState1Noop` is separately selected by `UpdateItemScreen`'s state-1 switch arm; common dialog/display work continues afterward.

## Function identities and EU source paths

Native size includes the original function's recorded bytes. ARM/Thumb mode is retained; the distinct empty entrypoints are not folded into a shared function.

### Confirmation and menu operations

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov075_020cead0` | `OpenItemPickerDiscardConfirmation` | THUMB / 0x1c | `src/overlays/ov075/calls/OpenItemPickerDiscardConfirmation.c` | Discard worker, header and disable-input callback pairs; returns 1. |
| `func_ov075_020ceaec` | `OpenItemPickerRewardConfirmation` | THUMB / 0x1c | `src/overlays/ov075/calls/OpenItemPickerRewardConfirmation.c` | Reward worker and menu callbacks; returns 1. |
| `func_ov075_020ce908` | `ConsumeItemPickerSelectionAndApplyReward` | THUMB / 0xc4 | `src/overlays/ov075/calls/ConsumeItemPickerSelectionAndApplyReward.c` | Reward/stock worker; always requests state 4/redraw. |
| `func_ov076_020ca8e0` | `OpenSlotMenuDiscardConfirmation` | THUMB / 0x1c | `src/overlays/ov076/calls/OpenSlotMenuDiscardConfirmation.c` | Slot owner; discard worker; returns 1. |
| `func_ov076_020ca8fc` | `OpenSlotMenuRewardConfirmation` | THUMB / 0x1c | `src/overlays/ov076/calls/OpenSlotMenuRewardConfirmation.c` | Slot owner; reward worker; returns 1. |
| `func_ov077_020c7914` | `OpenItemScreenDiscardConfirmation` | THUMB / 0x1c | `src/overlays/ov077/calls/OpenItemScreenDiscardConfirmation.c` | Item-screen owner; discard worker; returns 1. |
| `func_ov077_020c7930` | `OpenItemScreenRewardConfirmation` | THUMB / 0x1c | `src/overlays/ov077/calls/OpenItemScreenRewardConfirmation.c` | Item-screen owner; reward worker; returns 1. |
| `func_ov076_020ca918` | `ClearSlotMenuBg1AndRedrawSelection` | THUMB / 0x78 | `src/overlays/ov076/calls/ClearSlotMenuBg1AndRedrawSelection.c` | BG1 chars and selection-panel redraw guard; TRUE. |
| `func_ov077_020c794c` | `ClearItemScreenBg1AndRedrawList` | THUMB / 0x78 | `src/overlays/ov077/calls/ClearItemScreenBg1AndRedrawList.c` | BG1 chars and item-list redraw guard; TRUE. |
| `func_ov078_020c4df8` | `SelectPreviousMenuPage` | THUMB / 0xa8 | `src/overlays/ov078/calls/SelectPreviousMenuPage.c` | Previous page with count/mask-0x40 wrap guard. |
| `func_ov089_020befe0` | `MovePopupCursorOnDirectionalInput` | ARM / 0x34 | `src/overlays/ov089/calls/MovePopupCursorOnDirectionalInput.c` | Confirm mode plus directional mask gates element cursor. |
| `func_ov089_020c042c` | `ConfirmOrClosePopup` | ARM / 0x50 | `src/overlays/ov089/calls/ConfirmOrClosePopup.c` | Guard, close existing popup or enable confirmation. |
| `func_ov089_020c047c` | `CommitPopupSelectionToSessionBits` | ARM / 0x6c | `src/overlays/ov089/calls/CommitPopupSelectionToSessionBits.c` | Exact three-bit selected-ID encoding and close request. |
| `func_ov089_020c04e8` | `ResetPopupConfirmModeWithSound` | ARM / 0x2c | `src/overlays/ov089/calls/ResetPopupConfirmModeWithSound.c` | Sound then disable confirmation mode. |
| `func_ov103_020becc4` | `CommitTheaterEntrySelection` | ARM / 0x5c | `src/overlays/ov103/calls/CommitTheaterEntrySelection.c` | Phase/availability guard, store ID, request close. |
| `func_ov103_020bed20` | `CancelTheaterEntrySelection` | ARM / 0x3c | `src/overlays/ov103/calls/CancelTheaterEntrySelection.c` | Phase guard, store -1, close then sound. |
| `func_ov078_020c4f44` | `CloseOverlay078Menu` | THUMB / 0x1c | `src/overlays/ov078/calls/CloseOverlay078Menu.c` | Sound, stack pop, subscene (0,-1,0). |
| `func_ov075_020cec24` | `IsItemPickerPartyHpFull` | THUMB / 0x30 | `src/overlays/ov075/calls/IsItemPickerPartyHpFull.c` | All active records have current HP >= max HP. |
| `func_ov076_020caa34` | `IsSlotMenuPartyHpFull` | THUMB / 0x30 | `src/overlays/ov076/calls/IsSlotMenuPartyHpFull.c` | Same HP comparison, separate slot owner. |
| `func_ov077_020c7a68` | `IsItemScreenPartyHpFull` | THUMB / 0x30 | `src/overlays/ov077/calls/IsItemScreenPartyHpFull.c` | Same HP comparison, separate screen owner. |

### Popup task and window helpers

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov091_020c2774` | `ReportTopPopup_SetFlags` | ARM / 0x10 | `src/overlays/ov091/auto/ReportTopPopup_SetFlags.c` | PopupWindow +4 OR mask; residual is not ownership. |
| `func_ov091_020c2784` | `ReportTopPopup_ClearFlags` | ARM / 0x14 | `src/overlays/ov091/auto/ReportTopPopup_ClearFlags.c` | PopupWindow +4 AND-NOT mask. |
| `func_ov091_020c2798` | `ReportTopPopup_GetMaskedFlags` | ARM / 0xc | `src/overlays/ov091/auto/ReportTopPopup_GetMaskedFlags.c` | Raw PopupWindow flags & mask, not BOOL. |
| `func_ov091_020c27b4` | `ReportTopPopup_GetState` | ARM / 0x8 | `src/overlays/ov091/auto/ReportTopPopup_GetState.c` | Supplied PopupWindow +0 signed state. |
| `func_ov091_020c2804` | `ReportTopPopup_GetCurrentState` | ARM / 0x1c | `src/overlays/ov091/calls/ReportTopPopup_GetCurrentState.c` | Live global +0x2c window; returns signed state. |
| `func_ov091_020c27f8` | `ReportTopPopup_QueueMessage` | ARM / 0xc | `src/overlays/ov091/calls/ReportTopPopup_QueueMessage.c` | Four logical inputs; synchronous UTF-16 copy. |
| `func_ov091_020c27ec` | `ReportTopPopup_DestroyTask` | ARM / 0xc | `src/overlays/ov091/calls/ReportTopPopup_DestroyTask.c` | Task handle wrapper, not work/window ownership. |
| `func_ov093_020c3bb4` | `TrophyPopup_SetFlags` | ARM / 0x10 | `src/overlays/ov093/auto/TrophyPopup_SetFlags.c` | PopupWindow +4 OR mask; residual is not ownership. |
| `func_ov093_020c3bc4` | `TrophyPopup_ClearFlags` | ARM / 0x14 | `src/overlays/ov093/auto/TrophyPopup_ClearFlags.c` | PopupWindow +4 AND-NOT mask. |
| `func_ov093_020c3bd8` | `TrophyPopup_GetMaskedFlags` | ARM / 0xc | `src/overlays/ov093/auto/TrophyPopup_GetMaskedFlags.c` | Raw PopupWindow flags & mask, not BOOL. |
| `func_ov093_020c3bf4` | `TrophyPopup_GetState` | ARM / 0x8 | `src/overlays/ov093/auto/TrophyPopup_GetState.c` | Supplied PopupWindow +0 signed state. |
| `func_ov093_020c3c44` | `TrophyPopup_GetCurrentState` | ARM / 0x1c | `src/overlays/ov093/calls/TrophyPopup_GetCurrentState.c` | Live global +0x2c window; returns signed state. |
| `func_ov093_020c3c38` | `TrophyPopup_QueueMessage` | ARM / 0xc | `src/overlays/ov093/calls/TrophyPopup_QueueMessage.c` | Four logical inputs; synchronous UTF-16 copy. |
| `func_ov093_020c3c2c` | `TrophyPopup_DestroyTask` | ARM / 0xc | `src/overlays/ov093/calls/TrophyPopup_DestroyTask.c` | Task handle wrapper, not work/window ownership. |
| `func_ov091_020c1878` | `ReportTopPopup_InitTaskWork` | ARM / 0xb8 | `src/overlays/ov091/calls/ReportTopPopup_InitTaskWork.c` | Publishes running work; returns update code pointer. |
| `func_ov091_020c27bc` | `ReportTopPopup_CreateTask` | ARM / 0x30 | `src/overlays/ov091/calls/ReportTopPopup_CreateTask.c` | Descriptor ctor and TaskObject handle stored at +0. |

### Secondary placeholder lifecycle

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov090_020beac0` | `InitOv090SecondaryMenu` | ARM / 0x8 | `src/overlays/ov090/auto/InitOv090SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov090_020beac8` | `DestroyOv090SecondaryMenu` | ARM / 0x4 | `src/overlays/ov090/auto/DestroyOv090SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov090_020beacc` | `UpdateOv090SecondaryMenu` | ARM / 0x4 | `src/overlays/ov090/auto/UpdateOv090SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov092_020beac0` | `InitOv092SecondaryMenu` | ARM / 0x8 | `src/overlays/ov092/auto/InitOv092SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov092_020beac8` | `DestroyOv092SecondaryMenu` | ARM / 0x4 | `src/overlays/ov092/auto/DestroyOv092SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov092_020beacc` | `UpdateOv092SecondaryMenu` | ARM / 0x4 | `src/overlays/ov092/auto/UpdateOv092SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov094_020beac0` | `InitOv094SecondaryMenu` | ARM / 0x8 | `src/overlays/ov094/auto/InitOv094SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov094_020beac8` | `DestroyOv094SecondaryMenu` | ARM / 0x4 | `src/overlays/ov094/auto/DestroyOv094SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov094_020beacc` | `UpdateOv094SecondaryMenu` | ARM / 0x4 | `src/overlays/ov094/auto/UpdateOv094SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov096_020beac0` | `InitOv096SecondaryMenu` | ARM / 0x8 | `src/overlays/ov096/auto/InitOv096SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov096_020beac8` | `DestroyOv096SecondaryMenu` | ARM / 0x4 | `src/overlays/ov096/auto/DestroyOv096SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov096_020beacc` | `UpdateOv096SecondaryMenu` | ARM / 0x4 | `src/overlays/ov096/auto/UpdateOv096SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov098_020beac0` | `InitOv098SecondaryMenu` | ARM / 0x8 | `src/overlays/ov098/auto/InitOv098SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov098_020beac8` | `DestroyOv098SecondaryMenu` | ARM / 0x4 | `src/overlays/ov098/auto/DestroyOv098SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov098_020beacc` | `UpdateOv098SecondaryMenu` | ARM / 0x4 | `src/overlays/ov098/auto/UpdateOv098SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov100_020beac0` | `InitOv100SecondaryMenu` | ARM / 0x8 | `src/overlays/ov100/auto/InitOv100SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov100_020beac8` | `DestroyOv100SecondaryMenu` | ARM / 0x4 | `src/overlays/ov100/auto/DestroyOv100SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov100_020beacc` | `UpdateOv100SecondaryMenu` | ARM / 0x4 | `src/overlays/ov100/auto/UpdateOv100SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |
| `func_ov102_020beac0` | `InitOv102SecondaryMenu` | ARM / 0x8 | `src/overlays/ov102/auto/InitOv102SecondaryMenu.c` | Descriptor +0; literal 1 consumed as ready. |
| `func_ov102_020beac8` | `DestroyOv102SecondaryMenu` | ARM / 0x4 | `src/overlays/ov102/auto/DestroyOv102SecondaryMenu.c` | Descriptor +4; no body effects; residual discarded. |
| `func_ov102_020beacc` | `UpdateOv102SecondaryMenu` | ARM / 0x4 | `src/overlays/ov102/auto/UpdateOv102SecondaryMenu.c` | Descriptor +8; no body effects; residual propagated. |

### Outer state and caption hooks

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov073_020bff88` | `StatusMenu_UpdateOverviewInputNoop` | THUMB / 0x4 | `src/overlays/ov073/auto/StatusMenu_UpdateOverviewInputNoop.c` | Overview input update computes consumed zero. |
| `func_ov088_020bee58` | `UpdateOverlay088CaptionLayerNoop` | ARM / 0x4 | `src/overlays/ov088/auto/UpdateOverlay088CaptionLayerNoop.c` | Secondary descriptor update; residual propagated outward. |
| `func_ov091_020c1780` | `ReportTop_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov091/auto/ReportTop_HandleState0Noop.c` | Outer report state 0; common work continues. |
| `func_ov093_020c2374` | `TrophyReport_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov093/auto/TrophyReport_HandleState0Noop.c` | Outer trophy state 0; distinct from popup state. |
| `func_ov093_020c2b20` | `TrophyReport_HandleState6Noop` | ARM / 0x4 | `src/overlays/ov093/auto/TrophyReport_HandleState6Noop.c` | Outer trophy state 6; numerical state retained. |
| `func_ov095_020c1234` | `ItemGrid_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov095/auto/ItemGrid_HandleState0Noop.c` | Item-grid outer state 0. |
| `func_ov097_020c159c` | `StoryReport_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov097/auto/StoryReport_HandleState0Noop.c` | Story outer state 0; entry r0 is callback address. |
| `func_ov099_020c17a4` | `EnemyViewer_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov099/auto/EnemyViewer_HandleState0Noop.c` | Enemy-viewer outer state 0. |
| `func_ov101_020c17e0` | `Ov101List_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov101/auto/Ov101List_HandleState0Noop.c` | Ov101 outer list state 0; no stronger scene title. |

### Primary update and consumed input

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov078_020c4370` | `UpdatePageMenuNoop` | THUMB / 0x2 | `src/overlays/ov078/auto/UpdatePageMenuNoop.c` | Primary descriptor +8 update, not an input callback. |
| `func_ov080_020c5d28` | `SaveSelect_ConsumeLButtonNoop` | THUMB / 0x2 | `src/overlays/ov080/auto/SaveSelect_ConsumeLButtonNoop.c` | Present primary L slot consumes mask 0x200. |
| `func_ov080_020c5d2c` | `SaveSelect_ConsumeRButtonNoop` | THUMB / 0x2 | `src/overlays/ov080/auto/SaveSelect_ConsumeRButtonNoop.c` | Present primary R slot consumes mask 0x100. |

### State-entry and popup-window hooks

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov087_020c5cb0` | `SelectionPanel_EnterState8Noop` | ARM / 0x4 | `src/overlays/ov087/auto/SelectionPanel_EnterState8Noop.c` | State-entry slot 8 after common setup. |
| `func_ov087_020c5cb4` | `SelectionPanel_EnterState9Noop` | ARM / 0x4 | `src/overlays/ov087/auto/SelectionPanel_EnterState9Noop.c` | State-entry slot 9 after common setup. |
| `func_ov091_020c1dc0` | `ReportTopPopup_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov091/auto/ReportTopPopup_HandleState0Noop.c` | Embedded popup state 0; queue worker still runs. |
| `func_ov093_020c31f4` | `TrophyPopup_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov093/auto/TrophyPopup_HandleState0Noop.c` | Embedded trophy popup state 0. |

### Matrix cursor and substate hooks

| Original EU identity | Descriptive name | Mode / bytes | EU source | Evidence/contract |
|---|---|---|---|---|
| `func_ov075_020cc908` | `MatrixMenu_UpdatePage1CursorNoop` | THUMB / 0x2 | `src/overlays/ov075/auto/MatrixMenu_UpdatePage1CursorNoop.c` | Cursor registry index 0 -> page 1. |
| `func_ov075_020cc934` | `MatrixMenu_UpdatePage2CursorNoop` | THUMB / 0x2 | `src/overlays/ov075/auto/MatrixMenu_UpdatePage2CursorNoop.c` | Cursor registry index 1 -> page 2. |
| `func_ov075_020cc90c` | `MatrixMenu_UpdatePage5CursorNoop` | THUMB / 0x2 | `src/overlays/ov075/auto/MatrixMenu_UpdatePage5CursorNoop.c` | Cursor registry index 4 -> page 5. |
| `func_ov075_020d10fc` | `DestroyItemPickerSubstateNoop` | THUMB / 0x2 | `src/overlays/ov075/auto/DestroyItemPickerSubstateNoop.c` | Teardown hook on embedded work +0x34. |
| `func_ov076_020ccf30` | `DestroySlotMenuPanelSubstateNoop` | THUMB / 0x2 | `src/overlays/ov076/auto/DestroySlotMenuPanelSubstateNoop.c` | Slot-panel embedded-substate teardown hook. |
| `func_ov077_020c9f7c` | `DestroyItemScreenSubstateNoop` | THUMB / 0x2 | `src/overlays/ov077/auto/DestroyItemScreenSubstateNoop.c` | Item-screen embedded-substate teardown hook. |
| `func_ov077_020c4bcc` | `ItemScreen_HandleState1Noop` | THUMB / 0x2 | `src/overlays/ov077/auto/ItemScreen_HandleState1Noop.c` | Item-screen state-1 switch hook. |

## Reproducible byte-exact validation

Run the existing verifier from `eu/`. All 80 accepted entrypoints pass with
their native ARM/Thumb modes:

```sh
python tools/verify_idx.py src/overlays/ov075/calls/OpenItemPickerDiscardConfirmation.c OpenItemPickerDiscardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov075/calls/OpenItemPickerRewardConfirmation.c OpenItemPickerRewardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov075/calls/ConsumeItemPickerSelectionAndApplyReward.c ConsumeItemPickerSelectionAndApplyReward --thumb
python tools/verify_idx.py src/overlays/ov076/calls/OpenSlotMenuDiscardConfirmation.c OpenSlotMenuDiscardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov076/calls/OpenSlotMenuRewardConfirmation.c OpenSlotMenuRewardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov077/calls/OpenItemScreenDiscardConfirmation.c OpenItemScreenDiscardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov077/calls/OpenItemScreenRewardConfirmation.c OpenItemScreenRewardConfirmation --thumb
python tools/verify_idx.py src/overlays/ov076/calls/ClearSlotMenuBg1AndRedrawSelection.c ClearSlotMenuBg1AndRedrawSelection --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ClearItemScreenBg1AndRedrawList.c ClearItemScreenBg1AndRedrawList --thumb
python tools/verify_idx.py src/overlays/ov078/calls/SelectPreviousMenuPage.c SelectPreviousMenuPage --thumb
python tools/verify_idx.py src/overlays/ov089/calls/MovePopupCursorOnDirectionalInput.c MovePopupCursorOnDirectionalInput
python tools/verify_idx.py src/overlays/ov089/calls/ConfirmOrClosePopup.c ConfirmOrClosePopup
python tools/verify_idx.py src/overlays/ov089/calls/CommitPopupSelectionToSessionBits.c CommitPopupSelectionToSessionBits
python tools/verify_idx.py src/overlays/ov089/calls/ResetPopupConfirmModeWithSound.c ResetPopupConfirmModeWithSound
python tools/verify_idx.py src/overlays/ov103/calls/CommitTheaterEntrySelection.c CommitTheaterEntrySelection
python tools/verify_idx.py src/overlays/ov103/calls/CancelTheaterEntrySelection.c CancelTheaterEntrySelection
python tools/verify_idx.py src/overlays/ov078/calls/CloseOverlay078Menu.c CloseOverlay078Menu --thumb
python tools/verify_idx.py src/overlays/ov075/calls/IsItemPickerPartyHpFull.c IsItemPickerPartyHpFull --thumb
python tools/verify_idx.py src/overlays/ov076/calls/IsSlotMenuPartyHpFull.c IsSlotMenuPartyHpFull --thumb
python tools/verify_idx.py src/overlays/ov077/calls/IsItemScreenPartyHpFull.c IsItemScreenPartyHpFull --thumb
python tools/verify_idx.py src/overlays/ov091/auto/ReportTopPopup_SetFlags.c ReportTopPopup_SetFlags
python tools/verify_idx.py src/overlays/ov091/auto/ReportTopPopup_ClearFlags.c ReportTopPopup_ClearFlags
python tools/verify_idx.py src/overlays/ov091/auto/ReportTopPopup_GetMaskedFlags.c ReportTopPopup_GetMaskedFlags
python tools/verify_idx.py src/overlays/ov091/auto/ReportTopPopup_GetState.c ReportTopPopup_GetState
python tools/verify_idx.py src/overlays/ov091/calls/ReportTopPopup_GetCurrentState.c ReportTopPopup_GetCurrentState
python tools/verify_idx.py src/overlays/ov091/calls/ReportTopPopup_QueueMessage.c ReportTopPopup_QueueMessage
python tools/verify_idx.py src/overlays/ov091/calls/ReportTopPopup_DestroyTask.c ReportTopPopup_DestroyTask
python tools/verify_idx.py src/overlays/ov093/auto/TrophyPopup_SetFlags.c TrophyPopup_SetFlags
python tools/verify_idx.py src/overlays/ov093/auto/TrophyPopup_ClearFlags.c TrophyPopup_ClearFlags
python tools/verify_idx.py src/overlays/ov093/auto/TrophyPopup_GetMaskedFlags.c TrophyPopup_GetMaskedFlags
python tools/verify_idx.py src/overlays/ov093/auto/TrophyPopup_GetState.c TrophyPopup_GetState
python tools/verify_idx.py src/overlays/ov093/calls/TrophyPopup_GetCurrentState.c TrophyPopup_GetCurrentState
python tools/verify_idx.py src/overlays/ov093/calls/TrophyPopup_QueueMessage.c TrophyPopup_QueueMessage
python tools/verify_idx.py src/overlays/ov093/calls/TrophyPopup_DestroyTask.c TrophyPopup_DestroyTask
python tools/verify_idx.py src/overlays/ov091/calls/ReportTopPopup_InitTaskWork.c ReportTopPopup_InitTaskWork
python tools/verify_idx.py src/overlays/ov091/calls/ReportTopPopup_CreateTask.c ReportTopPopup_CreateTask
python tools/verify_idx.py src/overlays/ov090/auto/InitOv090SecondaryMenu.c InitOv090SecondaryMenu
python tools/verify_idx.py src/overlays/ov090/auto/DestroyOv090SecondaryMenu.c DestroyOv090SecondaryMenu
python tools/verify_idx.py src/overlays/ov090/auto/UpdateOv090SecondaryMenu.c UpdateOv090SecondaryMenu
python tools/verify_idx.py src/overlays/ov092/auto/InitOv092SecondaryMenu.c InitOv092SecondaryMenu
python tools/verify_idx.py src/overlays/ov092/auto/DestroyOv092SecondaryMenu.c DestroyOv092SecondaryMenu
python tools/verify_idx.py src/overlays/ov092/auto/UpdateOv092SecondaryMenu.c UpdateOv092SecondaryMenu
python tools/verify_idx.py src/overlays/ov094/auto/InitOv094SecondaryMenu.c InitOv094SecondaryMenu
python tools/verify_idx.py src/overlays/ov094/auto/DestroyOv094SecondaryMenu.c DestroyOv094SecondaryMenu
python tools/verify_idx.py src/overlays/ov094/auto/UpdateOv094SecondaryMenu.c UpdateOv094SecondaryMenu
python tools/verify_idx.py src/overlays/ov096/auto/InitOv096SecondaryMenu.c InitOv096SecondaryMenu
python tools/verify_idx.py src/overlays/ov096/auto/DestroyOv096SecondaryMenu.c DestroyOv096SecondaryMenu
python tools/verify_idx.py src/overlays/ov096/auto/UpdateOv096SecondaryMenu.c UpdateOv096SecondaryMenu
python tools/verify_idx.py src/overlays/ov098/auto/InitOv098SecondaryMenu.c InitOv098SecondaryMenu
python tools/verify_idx.py src/overlays/ov098/auto/DestroyOv098SecondaryMenu.c DestroyOv098SecondaryMenu
python tools/verify_idx.py src/overlays/ov098/auto/UpdateOv098SecondaryMenu.c UpdateOv098SecondaryMenu
python tools/verify_idx.py src/overlays/ov100/auto/InitOv100SecondaryMenu.c InitOv100SecondaryMenu
python tools/verify_idx.py src/overlays/ov100/auto/DestroyOv100SecondaryMenu.c DestroyOv100SecondaryMenu
python tools/verify_idx.py src/overlays/ov100/auto/UpdateOv100SecondaryMenu.c UpdateOv100SecondaryMenu
python tools/verify_idx.py src/overlays/ov102/auto/InitOv102SecondaryMenu.c InitOv102SecondaryMenu
python tools/verify_idx.py src/overlays/ov102/auto/DestroyOv102SecondaryMenu.c DestroyOv102SecondaryMenu
python tools/verify_idx.py src/overlays/ov102/auto/UpdateOv102SecondaryMenu.c UpdateOv102SecondaryMenu
python tools/verify_idx.py src/overlays/ov073/auto/StatusMenu_UpdateOverviewInputNoop.c StatusMenu_UpdateOverviewInputNoop --thumb
python tools/verify_idx.py src/overlays/ov088/auto/UpdateOverlay088CaptionLayerNoop.c UpdateOverlay088CaptionLayerNoop
python tools/verify_idx.py src/overlays/ov091/auto/ReportTop_HandleState0Noop.c ReportTop_HandleState0Noop
python tools/verify_idx.py src/overlays/ov093/auto/TrophyReport_HandleState0Noop.c TrophyReport_HandleState0Noop
python tools/verify_idx.py src/overlays/ov093/auto/TrophyReport_HandleState6Noop.c TrophyReport_HandleState6Noop
python tools/verify_idx.py src/overlays/ov095/auto/ItemGrid_HandleState0Noop.c ItemGrid_HandleState0Noop
python tools/verify_idx.py src/overlays/ov097/auto/StoryReport_HandleState0Noop.c StoryReport_HandleState0Noop
python tools/verify_idx.py src/overlays/ov099/auto/EnemyViewer_HandleState0Noop.c EnemyViewer_HandleState0Noop
python tools/verify_idx.py src/overlays/ov101/auto/Ov101List_HandleState0Noop.c Ov101List_HandleState0Noop
python tools/verify_idx.py src/overlays/ov078/auto/UpdatePageMenuNoop.c UpdatePageMenuNoop --thumb
python tools/verify_idx.py src/overlays/ov080/auto/SaveSelect_ConsumeLButtonNoop.c SaveSelect_ConsumeLButtonNoop --thumb
python tools/verify_idx.py src/overlays/ov080/auto/SaveSelect_ConsumeRButtonNoop.c SaveSelect_ConsumeRButtonNoop --thumb
python tools/verify_idx.py src/overlays/ov087/auto/SelectionPanel_EnterState8Noop.c SelectionPanel_EnterState8Noop
python tools/verify_idx.py src/overlays/ov087/auto/SelectionPanel_EnterState9Noop.c SelectionPanel_EnterState9Noop
python tools/verify_idx.py src/overlays/ov091/auto/ReportTopPopup_HandleState0Noop.c ReportTopPopup_HandleState0Noop
python tools/verify_idx.py src/overlays/ov093/auto/TrophyPopup_HandleState0Noop.c TrophyPopup_HandleState0Noop
python tools/verify_idx.py src/overlays/ov075/auto/MatrixMenu_UpdatePage1CursorNoop.c MatrixMenu_UpdatePage1CursorNoop --thumb
python tools/verify_idx.py src/overlays/ov075/auto/MatrixMenu_UpdatePage2CursorNoop.c MatrixMenu_UpdatePage2CursorNoop --thumb
python tools/verify_idx.py src/overlays/ov075/auto/MatrixMenu_UpdatePage5CursorNoop.c MatrixMenu_UpdatePage5CursorNoop --thumb
python tools/verify_idx.py src/overlays/ov075/auto/DestroyItemPickerSubstateNoop.c DestroyItemPickerSubstateNoop --thumb
python tools/verify_idx.py src/overlays/ov076/auto/DestroySlotMenuPanelSubstateNoop.c DestroySlotMenuPanelSubstateNoop --thumb
python tools/verify_idx.py src/overlays/ov077/auto/DestroyItemScreenSubstateNoop.c DestroyItemScreenSubstateNoop --thumb
python tools/verify_idx.py src/overlays/ov077/auto/ItemScreen_HandleState1Noop.c ItemScreen_HandleState1Noop --thumb
bash tools/gate.sh
```

The fresh gate passes all 108 linked modules. Affected production function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. Descriptor contents are preserved;
empty entrypoints remain distinct. These names add no C or DATA matching credit.
No algorithm or callback-return ABI change is part of this block.
