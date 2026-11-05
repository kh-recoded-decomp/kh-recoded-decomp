# Menu state, navigation and report helper contracts

This block covers the remaining 49 reviewed EU menu/report entrypoints in overlays 073-103 at baseline 00280f. The separate menu80 block, published names and unresolved late-overlay holds are excluded. Parallel native wrappers and owners remain distinct. Names record observed operations, writers and consumers; numerical states and opaque fields retain operational descriptions.

Source paths in the identity table are relative to `eu/` and use the accepted names. Shared-source suffixes retain reference-region addresses; the original identities/modes identify EU. No signature or algorithm change is bundled. Erased legacy signatures are documented for a later port instead of being changed to influence code generation.

## Status owner and selected records

`DestroyStatusMenu` is the registered teardown for the 0x1230-byte secondary owner. It preserves the page-4 guard and release order for object lists, strings, record slot/manager and widgets. One internal helper's wider role remains opaque; descriptor/caller evidence independently establishes the teardown role.

The progress comparator subtracts entry B's first u32 ID from entry A's ID under the real signed qsort convention. Preserve native 32-bit subtraction; this is not sorting localized names or percentages. `GetStatusListSelectedRecordIndex` returns -1 for selected usage state 3; otherwise it returns the selected eight-byte entry's first u16. Consumers perform record lookup or fallback-message rendering. No new bounds guards or gameplay meaning for usage 3 is established.

## Panel state, session words and threshold ranks

`ItemPickerAbsInt32` uses native arithmetic-sign and bitwise absolute-value operations. INT_MIN retains bits 0x80000000; a host signed abs with different overflow behavior is not equivalent.

Picker panel state +4 and input-block word +8 are distinct. Initialization/open/close writers and update consumers prove that state zero stops the picker updater, while input is permitted only with +8 zero. Timer/closing labels do not prove units or lifecycle for +8. `GetSlotMenuItemPanelState` reads the embedded panel state at global SlotMenu +0x28, not the primary state at +0 or a separate panel-work global. Returns are full raw words without added NULL/bounds guards.

The three `Is...SessionState10` predicates compare singleton session +0x27a8 with literal 10. Item/reward consumers distinguish types 0xb9/0xba but do not establish an idle, ready or difficulty enum. This field is separate from participant HP and selection values.

Both threshold-rank bonus helpers read/write the same halfword at EU 0x020608da: `GetSelectionPackedValueBlock()+0x0a` aliases the setter's base +0x12. They quantize through five threshold/value pairs: (1000,0), (3900,2450), (7000,5450), (10300,8650), (10300,10300). Bonus is added to the rank, capped above at 4, then the row value is written. It is not added directly to the halfword. There is no lower-rank clamp.

Keep the special paths: context 5 with packed state other than 2 writes 3300 only when flags 0x3609/0x360a are both set and bonus>0; context 3 outside worlds 0x1d/0x1e skips. Only the ordinary table path synchronizes list scroll. No gameplay identity for the value is proven; parallel tables/implementations stay separate.

## Slot edit, fusion and transition

`SlotMenu_EnterSlotEditState` enters state 1, clears +0x1c6f4 and shows its hint. A set one-shot field +0x4a074 is cleared and suppresses root-navigation enabling for that call. State 1 dispatches the edit-screen worker; browse is state 0, making the old ResetToBrowse alias misleading. No timer units are inferred for the cleared word.

`SlotMenu_GetSpecialFusionResult` returns raw +0x0c. The fusion writer returns nonzero for a gained record-kind bit or special +10 level result; ordinary +1..+5 level outcomes can return zero. The stored result selects state 10 versus 5 and is used as a hint-open predicate. It is neither general fusion success nor an owned selection pointer despite a private pointer view.

The state-6 transition wait disables secondary input, refreshes the view, decrements u8 +0x49857 and starts scrolling at zero. The initializer supplies 25 frames; the next worker advances to state 7. Preserve decrement/underflow from zero and call order. Screen-to-model conversion is exactly `X=((x+7)<<12)+0x80`, `Y=(192-(y+8))<<12`; callers supply Z separately. Retain the fractional X correction and asymmetric Y mapping.

## Destinations and thunks

The actual ov039 registry proves scene 1 selects Matrix ov075, 2 Slot ov076 and 3 ItemScreen ov077. Scene 0 selects ov074; its wider role is unnamed. StartSubScene's third argument marks pending secondary setup, not automatically pop/exit/blend.

Slot navigation requires state 1, zero gate +0x28 and point-limit validation. Its scene-0 path replaces the stack top using flag 0xf5b. ItemScreen instead requires state +0x7fb0 equal 4 and zero gate +0x18, lacks that point-limit check, and uses different scene-0 stack values. Matrix/item/slot open callbacks reset header text and use their exact FALSE flag. Preserve per-owner guards, sounds and stack operations.

Slot refresh thunks for states 3/8/9 all forward to Thumb target 0x020c5c01. Hint targets are slot 0x020c8199, ItemScreen 0x020c5965 and tutorial indicator 0x020c57b1. Register arguments, result, Thumb bit, distinct entrypoints and literal pools survive unchanged. No extra update/render work occurs in a thunk.

The enemy-viewer ARM thunk forwards `(work+0xd0ec, selectedEnemy)` to the actual selection-model loader; its caller ignores the result. The theater pool thunk targets InitSlotPool at 0x020bf688, which initializes the intrusive list at scene +0x174. Its complete descriptor-lifecycle role is not recovered; the name claims only the proven target.

## Tutorial and selection-panel lifetimes

The ov081 selected-entry wrapper forwards the selected slot from ov082 into the entry accessor; the old arithmetic template loses that input. Tutorial state is a borrowed global used by the ov082 list initializer. Text accessors use separate packed views at +8 (tuto) and +0x14 (list). Native tail calls and real renderers consume pointer results despite void legacy definitions. Strings are borrowed from their table owner. Closing ov081 sounds, pops and requests `(0,-1,TRUE)`; its final flag differs from ov078's similar close wrapper.

Widget 7 commits the selected destination from a 0x108-byte page record only with guard +0x10 zero. Kind +0xbc0 dispatches: 0 restores a saved field request and clears mask 0x4000; 1 calls EnterSceneSlot; 2 calls PlayFieldTrackSet with selection live in r0; 3 calls EnterSceneSlotAtSpawn. The case-2 C call erases that real input. Unknown kinds also execute the common clear-resume/close/sound tail. No gameplay titles are assigned to kinds. Widget 8 uses the same opaque guard before PopPanelState(scene,1); it is not identified as a loading/animation timer or a specific device/icon.

## Root teardown and report states

Ov078/089 root wrappers destroy elements then release embedded manager resources only for root +0x6478 mask 4. The root remains owned by the menu system; +0x647c is a separate container view. Ov089 primary-element reset uses mode 0, suppressing its optional per-entry release callback. It does not free all resources or hide all graphics.

Paired writers/dispatchers establish ItemGrid mode +0x1110c, StoryReport state +0xf06c, EnemyViewer state +0xd6ec and Theater phase +0xcb88 as distinct owner fields. Story's setter takes state before scene, writes state and clears +0xf070/+0xf074. EnemyViewer's selected-model mode +0x5bc is different. Theater input callers erase the real scene argument; a host port must restore forwarding.

Opaque Story gauge rendering passes FALSE for translucency. The scrolled-popup final Noop runs after normal copies/draws, with no explicit argument setup or body work. Its unspecified residual r0 propagates through the draw epilogue until the sole frame caller overwrites it with zero. Do not invent scene input or result identity. Theater's state-0 Noop receives scene; that pointer propagates through state/primary dispatch until all eight audited lifecycle callers overwrite it. State 0 is not named idle/complete.

Ov101's VBlank Noop is registered by name on channel 0, with callback as the actual third registration argument. The ISR calls it without explicit input, then advances the linked node and overwrites r0. Incoming r0 is the callback address, not scene work. Shutdown unregisters the same channel/name before list teardown. Preserve registration presence/lifetime; it is separate from the scene's state-0 hook.

## Per-function identity and evidence

The integration plan retains detailed paired sources and limits for every row.

| Original EU symbol | Descriptive name | Mode / bytes | EU source | Primary evidence |
|---|---|---|---|---|
| `func_ov073_020bfbec` | `DestroyStatusMenu` | THUMB / 0x8c | `src/overlays/ov073/calls/DestroyStatusMenu.c` | `eu/src/ov073/data/Data_ov073_020c4160.c:11` |
| `func_ov073_020c1ce0` | `CompareStatusProgressEntryId` | THUMB / 0x8 | `src/overlays/ov073/auto/CompareStatusProgressEntryId.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c:535` |
| `func_ov073_020c3fc4` | `GetStatusListSelectedRecordIndex` | THUMB / 0x24 | `src/overlays/ov073/calls/GetStatusListSelectedRecordIndex.c` | `src/ov073/status_menu/ShowSelectedRecordName_020c1a00.c:55` |
| `func_ov075_020c7bf4` | `ItemPickerAbsInt32` | ARM / 0xc | `src/overlays/ov075/calls/ItemPickerAbsInt32.c` | `eu/src/overlays/ov075/calls/ItemPickerAbsInt32.c:2` |
| `func_ov075_020c7d14` | `GetItemPickerPanelInputBlockState` | ARM / 0x8 | `src/overlays/ov075/auto/GetItemPickerPanelInputBlockState.c` | `src/ov075/unclassified_helpers/ItemMenu_Update_020d026c.c:200` |
| `func_ov075_020c7d1c` | `GetItemPickerPanelState` | ARM / 0x8 | `src/overlays/ov075/auto/GetItemPickerPanelState.c` | `src/ov075/unclassified_helpers/func_ov075_020d0014.c:178` |
| `func_ov075_020ced2c` | `IsItemPickerSessionState10` | THUMB / 0x1c | `src/overlays/ov075/calls/IsItemPickerSessionState10.c` | `src/ov075/unclassified_helpers/IsRewardEntryLocked_020ced28.c:80` |
| `func_ov076_020c4ec8` | `SlotMenu_EnterSlotEditState` | THUMB / 0x34 | `src/overlays/ov076/calls/SlotMenu_EnterSlotEditState.c` | `eu/src/overlays/ov076/calls/SlotMenu_UpdateBrowse.c:52` |
| `func_ov076_020c5264` | `SlotMenu_GetSpecialFusionResult` | THUMB / 0x4 | `src/overlays/ov076/auto/SlotMenu_GetSpecialFusionResult.c` | `src/ov076/unclassified_helpers/SlotMenu_UpdateMessageWait_020c5c14.c:24` |
| `func_ov076_020c5c2c` | `SlotMenu_RefreshViewState3Thunk` | THUMB / 0x8 | `src/overlays/ov076/calls/SlotMenu_RefreshViewState3Thunk.c` | `src/ov076/unclassified_helpers/SlotMenu_Update_020c4b48.c:66` |
| `func_ov076_020c5ca0` | `SlotMenu_UpdateSlotTransitionWait` | THUMB / 0x2c | `src/overlays/ov076/calls/SlotMenu_UpdateSlotTransitionWait.c` | `eu/src/overlays/ov076/calls/SlotMenu_BeginSlotTransition.c:47` |
| `func_ov076_020c5d30` | `SlotMenu_RefreshViewState8Thunk` | THUMB / 0x8 | `src/overlays/ov076/calls/SlotMenu_RefreshViewState8Thunk.c` | `src/ov076/unclassified_helpers/SlotMenu_Update_020c4b48.c:79` |
| `func_ov076_020c5d38` | `SlotMenu_RefreshViewState9Thunk` | THUMB / 0x8 | `src/overlays/ov076/calls/SlotMenu_RefreshViewState9Thunk.c` | `src/ov076/unclassified_helpers/SlotMenu_Update_020c4b48.c:82` |
| `func_ov076_020c7714` | `SlotMenu_MapScreenPointToModelXY` | THUMB / 0x14 | `src/overlays/ov076/calls/SlotMenu_MapScreenPointToModelXY.c` | `src/ov076/matrix_menu/SlotMenu_DrawSlotModels_020c7708.c:119` |
| `func_ov076_020c8d40` | `SlotMenu_SwitchToScene0` | THUMB / 0x50 | `src/overlays/ov076/calls/SlotMenu_SwitchToScene0.c` | `eu/src/ov076/data/Data_ov076_020cd2f8.c:27` |
| `func_ov076_020c8e8c` | `SlotMenu_OpenMatrixMenu` | THUMB / 0x42 | `src/overlays/ov076/calls/SlotMenu_OpenMatrixMenu.c` | `eu/src/ov076/data/Data_ov076_020cd2f8.c:30` |
| `func_ov076_020c8ed0` | `SlotMenu_OpenItemScreen` | THUMB / 0x40 | `src/overlays/ov076/calls/SlotMenu_OpenItemScreen.c` | `eu/src/ov076/data/Data_ov076_020cd2f8.c:31` |
| `func_ov076_020c8f10` | `SlotMenu_DrawHintTextThunk` | THUMB / 0x8 | `src/overlays/ov076/calls/SlotMenu_DrawHintTextThunk.c` | `src/ov076/unclassified_helpers/SlotMenu_Init_020c45a8.c:64` |
| `func_ov076_020c8f44` | `GetSlotMenuItemPanelState` | THUMB / 0xc | `src/overlays/ov076/auto/GetSlotMenuItemPanelState.c` | `src/ov076/unclassified_helpers/SlotMenu_Init_020c45a8.c:95` |
| `func_ov076_020ca560` | `ApplySlotMenuThresholdRankBonus` | THUMB / 0xc8 | `src/overlays/ov076/calls/ApplySlotMenuThresholdRankBonus.c` | `eu/src/ov076/data/Rodata_ov076_020cd140.c:14` |
| `func_ov076_020cab3c` | `IsSlotMenuSessionState10` | THUMB / 0x1c | `src/overlays/ov076/calls/IsSlotMenuSessionState10.c` | `src/ov076/unclassified_helpers/ItemList_IsRewardEntryLocked_020cab38.c:80` |
| `func_ov077_020c5db8` | `ItemScreen_SwitchToScene0` | THUMB / 0x40 | `src/overlays/ov077/calls/ItemScreen_SwitchToScene0.c` | `eu/src/ov077/data/Data_ov077_020ca2a0.c:28` |
| `func_ov077_020c5f14` | `ItemScreen_OpenSlotMenu` | THUMB / 0x34 | `src/overlays/ov077/calls/ItemScreen_OpenSlotMenu.c` | `eu/src/ov077/data/Data_ov077_020ca2a0.c:31` |
| `func_ov077_020c5f48` | `ItemScreen_OpenMatrixMenu` | THUMB / 0x34 | `src/overlays/ov077/calls/ItemScreen_OpenMatrixMenu.c` | `eu/src/ov077/data/Data_ov077_020ca2a0.c:32` |
| `func_ov077_020c5f7c` | `ItemScreen_DrawHintTextThunk` | THUMB / 0x8 | `src/overlays/ov077/calls/ItemScreen_DrawHintTextThunk.c` | `eu/src/overlays/ov077/calls/InitItemScreen.c:97` |
| `func_ov077_020c7594` | `ApplyItemScreenThresholdRankBonus` | THUMB / 0xc8 | `src/overlays/ov077/calls/ApplyItemScreenThresholdRankBonus.c` | `eu/src/ov077/data/Rodata_ov077_020ca170.c:14` |
| `func_ov077_020c7b70` | `IsItemScreenSessionState10` | THUMB / 0x1c | `src/overlays/ov077/calls/IsItemScreenSessionState10.c` | `src/ov077/unclassified_helpers/CanUseItemEntry_020c7b6c.c:72` |
| `func_ov078_020c4728` | `DestroyPageMenuRootElements` | THUMB / 0x14 | `src/overlays/ov078/calls/DestroyPageMenuRootElements.c` | `src/ov078/unclassified_helpers/ShutdownPageMenu_020c4354.c:25` |
| `func_ov081_020c544c` | `GetOverlay081EntryForSelectedSlot` | THUMB / 0xc | `src/overlays/ov081/calls/GetOverlay081EntryForSelectedSlot.c` | `src/ov081/library_nitro_fx/FX_Div_020c542c.c:4` |
| `func_ov081_020c5478` | `DrawTutorialPageIndicatorThunk` | THUMB / 0x8 | `src/overlays/ov081/calls/DrawTutorialPageIndicatorThunk.c` | `eu/src/ov081/data/Data_ov081_020c5cc0.c:15` |
| `func_ov081_020c5a78` | `CloseOverlay081Menu` | THUMB / 0x1c | `src/overlays/ov081/calls/CloseOverlay081Menu.c` | `eu/src/overlays/ov081/calls/CloseOverlay081Menu.c:7` |
| `func_ov081_020c5bf8` | `GetTutorialMenuState` | THUMB / 0xc | `src/overlays/ov081/calls/GetTutorialMenuState.c` | `eu/src/overlays/ov082/calls/InitOv082EntryList.c:47` |
| `func_ov081_020c5c04` | `GetTutorialTextEntry` | THUMB / 0x14 | `src/overlays/ov081/calls/GetTutorialTextEntry.c` | `src/ov081/unclassified_helpers/InitOv081Screen_020c4c30.c:67` |
| `func_ov081_020c5c18` | `GetTutorialListTextEntry` | THUMB / 0x14 | `src/overlays/ov081/calls/GetTutorialListTextEntry.c` | `src/ov081/unclassified_helpers/InitOv081Screen_020c4c30.c:68` |
| `func_ov087_020c7b84` | `SelectionPanel_CommitDestination` | ARM / 0x94 | `src/overlays/ov087/calls/SelectionPanel_CommitDestination.c` | `src/ov087/panel_state/SetupPanelWidgetHandlers_020c69a4.c:41` |
| `func_ov087_020c7c18` | `HandlePanelBackWidget` | ARM / 0x20 | `src/overlays/ov087/calls/HandlePanelBackWidget.c` | `src/ov087/panel_state/SetupPanelWidgetHandlers_020c69a4.c:42` |
| `func_ov089_020bf4a8` | `ClearOverlay089PrimaryElementRecords` | ARM / 0x14 | `src/overlays/ov089/calls/ClearOverlay089PrimaryElementRecords.c` | `src/ov089/panel_state/ShutdownOverlay089_020c01b4.c:14` |
| `func_ov089_020bfaf0` | `DestroyOverlay089RootElements` | ARM / 0x18 | `src/overlays/ov089/calls/DestroyOverlay089RootElements.c` | `src/ov089/panel_state/ShutdownOverlay089_020c01b4.c:16` |
| `func_ov095_020c1228` | `GetItemGridPanelMode` | ARM / 0xc | `src/overlays/ov095/auto/GetItemGridPanelMode.c` | `src/ov095/leaf_research/func_ov095_020c1208.c:2` |
| `func_ov097_020c1578` | `SetStoryReportState` | ARM / 0x18 | `src/overlays/ov097/calls/SetStoryReportState.c` | `eu/src/overlays/ov097/calls/SetStoryReportState.c:10` |
| `func_ov097_020c1590` | `GetStoryReportState` | ARM / 0xc | `src/overlays/ov097/auto/GetStoryReportState.c` | `src/ov097/leaf_research/func_ov097_020c1570.c:2` |
| `func_ov097_020c1a64` | `StoryReport_FinalizeScrolledPopupDrawNoop` | THUMB / 0x2 | `src/overlays/ov097/auto/StoryReport_FinalizeScrolledPopupDrawNoop.c` | `src/ov097/panel_state/DrawScrolledPopups_020c0d70.c:41` |
| `func_ov097_020c1db8` | `DrawStoryReportGaugeOpaque` | THUMB / 0xc | `src/overlays/ov097/calls/DrawStoryReportGaugeOpaque.c` | `src/ov097/library_nitro_nns/NNS_FndInitListWithOffset0_020c1d98.c:3` |
| `func_ov099_020c1798` | `GetEnemyViewerMode` | ARM / 0xc | `src/overlays/ov099/auto/GetEnemyViewerMode.c` | `src/ov099/leaf_research/func_ov099_020c1778.c:2` |
| `func_ov099_020c2260` | `LoadEnemyViewerSelectionModelsThunk` | ARM / 0xc | `src/overlays/ov099/calls/LoadEnemyViewerSelectionModelsThunk.c` | `src/ov099/unclassified_helpers/RunViewerIntroMode_020c1788.c:12` |
| `func_ov101_020c1980` | `Ov101List_VBlankNoop` | ARM / 0x4 | `src/overlays/ov101/auto/Ov101List_VBlankNoop.c` | `eu/src/overlays/ov101/calls/InitializeListScene.c:80` |
| `func_ov103_020c032c` | `GetTheaterReportPhase` | ARM / 0xc | `src/overlays/ov103/auto/GetTheaterReportPhase.c` | `src/ov103/leaf_research/func_ov103_020c030c.c:2` |
| `func_ov103_020c0338` | `TheaterReport_HandleState0Noop` | ARM / 0x4 | `src/overlays/ov103/auto/TheaterReport_HandleState0Noop.c` | `eu/src/ov103/data/Rodata_ov103_020c049c.c:9` |
| `func_ov103_020c0490` | `InitTheaterReportSlotPoolThunk` | ARM / 0xc | `src/overlays/ov103/calls/InitTheaterReportSlotPoolThunk.c` | `src/ov103/panel_state/InitSlotPool_020bf668.c:12` |

## Reproducible byte-exact validation

Run from `eu/` using the existing tools:

```sh
python tools/verify_idx.py src/overlays/ov073/calls/DestroyStatusMenu.c DestroyStatusMenu --thumb
python tools/verify_idx.py src/overlays/ov073/auto/CompareStatusProgressEntryId.c CompareStatusProgressEntryId --thumb
python tools/verify_idx.py src/overlays/ov073/calls/GetStatusListSelectedRecordIndex.c GetStatusListSelectedRecordIndex --thumb
python tools/verify_idx.py src/overlays/ov075/calls/ItemPickerAbsInt32.c ItemPickerAbsInt32
python tools/verify_idx.py src/overlays/ov075/auto/GetItemPickerPanelInputBlockState.c GetItemPickerPanelInputBlockState
python tools/verify_idx.py src/overlays/ov075/auto/GetItemPickerPanelState.c GetItemPickerPanelState
python tools/verify_idx.py src/overlays/ov075/calls/IsItemPickerSessionState10.c IsItemPickerSessionState10 --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_EnterSlotEditState.c SlotMenu_EnterSlotEditState --thumb
python tools/verify_idx.py src/overlays/ov076/auto/SlotMenu_GetSpecialFusionResult.c SlotMenu_GetSpecialFusionResult --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_RefreshViewState3Thunk.c SlotMenu_RefreshViewState3Thunk --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_UpdateSlotTransitionWait.c SlotMenu_UpdateSlotTransitionWait --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_RefreshViewState8Thunk.c SlotMenu_RefreshViewState8Thunk --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_RefreshViewState9Thunk.c SlotMenu_RefreshViewState9Thunk --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_MapScreenPointToModelXY.c SlotMenu_MapScreenPointToModelXY --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_SwitchToScene0.c SlotMenu_SwitchToScene0 --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_OpenMatrixMenu.c SlotMenu_OpenMatrixMenu --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_OpenItemScreen.c SlotMenu_OpenItemScreen --thumb
python tools/verify_idx.py src/overlays/ov076/calls/SlotMenu_DrawHintTextThunk.c SlotMenu_DrawHintTextThunk --thumb
python tools/verify_idx.py src/overlays/ov076/auto/GetSlotMenuItemPanelState.c GetSlotMenuItemPanelState --thumb
python tools/verify_idx.py src/overlays/ov076/calls/ApplySlotMenuThresholdRankBonus.c ApplySlotMenuThresholdRankBonus --thumb
python tools/verify_idx.py src/overlays/ov076/calls/IsSlotMenuSessionState10.c IsSlotMenuSessionState10 --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ItemScreen_SwitchToScene0.c ItemScreen_SwitchToScene0 --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ItemScreen_OpenSlotMenu.c ItemScreen_OpenSlotMenu --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ItemScreen_OpenMatrixMenu.c ItemScreen_OpenMatrixMenu --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ItemScreen_DrawHintTextThunk.c ItemScreen_DrawHintTextThunk --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ApplyItemScreenThresholdRankBonus.c ApplyItemScreenThresholdRankBonus --thumb
python tools/verify_idx.py src/overlays/ov077/calls/IsItemScreenSessionState10.c IsItemScreenSessionState10 --thumb
python tools/verify_idx.py src/overlays/ov078/calls/DestroyPageMenuRootElements.c DestroyPageMenuRootElements --thumb
python tools/verify_idx.py src/overlays/ov081/calls/GetOverlay081EntryForSelectedSlot.c GetOverlay081EntryForSelectedSlot --thumb
python tools/verify_idx.py src/overlays/ov081/calls/DrawTutorialPageIndicatorThunk.c DrawTutorialPageIndicatorThunk --thumb
python tools/verify_idx.py src/overlays/ov081/calls/CloseOverlay081Menu.c CloseOverlay081Menu --thumb
python tools/verify_idx.py src/overlays/ov081/calls/GetTutorialMenuState.c GetTutorialMenuState --thumb
python tools/verify_idx.py src/overlays/ov081/calls/GetTutorialTextEntry.c GetTutorialTextEntry --thumb
python tools/verify_idx.py src/overlays/ov081/calls/GetTutorialListTextEntry.c GetTutorialListTextEntry --thumb
python tools/verify_idx.py src/overlays/ov087/calls/SelectionPanel_CommitDestination.c SelectionPanel_CommitDestination
python tools/verify_idx.py src/overlays/ov087/calls/HandlePanelBackWidget.c HandlePanelBackWidget
python tools/verify_idx.py src/overlays/ov089/calls/ClearOverlay089PrimaryElementRecords.c ClearOverlay089PrimaryElementRecords
python tools/verify_idx.py src/overlays/ov089/calls/DestroyOverlay089RootElements.c DestroyOverlay089RootElements
python tools/verify_idx.py src/overlays/ov095/auto/GetItemGridPanelMode.c GetItemGridPanelMode
python tools/verify_idx.py src/overlays/ov097/calls/SetStoryReportState.c SetStoryReportState
python tools/verify_idx.py src/overlays/ov097/auto/GetStoryReportState.c GetStoryReportState
python tools/verify_idx.py src/overlays/ov097/auto/StoryReport_FinalizeScrolledPopupDrawNoop.c StoryReport_FinalizeScrolledPopupDrawNoop --thumb
python tools/verify_idx.py src/overlays/ov097/calls/DrawStoryReportGaugeOpaque.c DrawStoryReportGaugeOpaque --thumb
python tools/verify_idx.py src/overlays/ov099/auto/GetEnemyViewerMode.c GetEnemyViewerMode
python tools/verify_idx.py src/overlays/ov099/calls/LoadEnemyViewerSelectionModelsThunk.c LoadEnemyViewerSelectionModelsThunk
python tools/verify_idx.py src/overlays/ov101/auto/Ov101List_VBlankNoop.c Ov101List_VBlankNoop
python tools/verify_idx.py src/overlays/ov103/auto/GetTheaterReportPhase.c GetTheaterReportPhase
python tools/verify_idx.py src/overlays/ov103/auto/TheaterReport_HandleState0Noop.c TheaterReport_HandleState0Noop
python tools/verify_idx.py src/overlays/ov103/calls/InitTheaterReportSlotPoolThunk.c InitTheaterReportSlotPoolThunk
bash tools/gate.sh
```

All 49 official function checks pass. The fresh gate passes all 108 linked
modules. Affected function bytes, resolved relocation targets/types and addends,
and all module hashes match the preserved baseline. Guards, encodings, raw
results, callback presence and thunk literals remain unchanged. This block
adds no C or DATA reconstruction credit.
