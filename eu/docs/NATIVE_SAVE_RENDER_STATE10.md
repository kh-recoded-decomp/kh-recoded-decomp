# Save, model and collision DATA owners (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The 32-byte SaveIoState contract spans a 12-byte prefix and a 20-byte continuation. Its continuation starts with the active payload pointer, but also holds callback/result/tick state. Category counters similarly have larger pointer views reaching separate trailing symbols. These views must not become smaller host allocations just because only the leading field has a convenient declaration.

The save-slot menu flag is distinct from validation status: the writer counts every nonzero slot status, including the error status 1. Rendering/collision globals are shared dispatch and scratch storage; their names do not establish reentrancy or per-object ownership.

## Inventory and evidence

### `main:0205fe00` → `gSaveIoStatePrefix`

Previous label `data_0205fe00`; size **12 bytes**; source `eu/src/data/bss/Bss_main_0205fe00.c`.

12 BSS bytes: block counter byte, slot byte, lock ID halfword, transfer-thread pointer and save-slot buffer pointer. It is the native prefix of the 32-byte SaveIoState view.

InitSaveSystem obtains the CARD lock ID and allocates the 0x3c18-byte save-slot buffer. StartCardTransferThread stores the allocated thread pointer at +4. BeginSaveSlotWrite uses the lock, updates the first two bytes and hashes the buffer before queuing a write.

Limits: The native object is only 12 bytes; the full SaveIoState view continues into the separate 20-byte object at fe0c. Preserve both allocation boundaries, all shared aliases and the 32-bit pointer ABI.

Pinned references:

- `eu/src/SaveIoState.h`; line(s) 49.
- `eu/src/calls/BeginSaveSlotWrite.c`; line(s) 26, 29, 34, 35, 36, 37, 39, 41, 42, 43, 44, 45, 46, 47.
- `eu/src/calls/CardTransferThreadMain.c` → `src/arm9/shared_engine/CardTransferThreadMain_02026b58.c`; line(s) 18, 38, 40, 41, 44.
- `eu/src/calls/ClearGlobalPackedBit.c` → `src/arm9/packed_bits/ClearGlobalPackedBit_02027334.c`; line(s) 8, 13.
- `eu/src/calls/CountSetBitsInMainFlagArray.c` → `src/arm9/unclassified_helpers/func_020275e4.c`; line(s) 8, 12.
- `eu/src/calls/EquipRecordList.c` → `src/arm9/indexed_records/EquipRecordList_02027858.c`; line(s) 61, 66.
- `eu/src/calls/FormatSaveData.c` → `src/arm9/shared_engine/FormatSaveData_02026ea0.c`; line(s) 8, 20, 25.
- `eu/src/calls/GetBit26Flag.c` → `src/arm9/unclassified_helpers/func_020273a8.c`; line(s) 8, 12.
- `eu/src/calls/GetCardThreadStartTick.c` → `src/arm9/shared_engine/GetCardThreadStartTick_0202726c.c`; line(s) 8, 12.
- `eu/src/calls/GetSlotFlagsField.c` → `src/arm9/unclassified_helpers/func_020273c0.c`; line(s) 8, 12.
- `eu/src/calls/InitSaveData.c` → `src/arm9/shared_records/InitSaveData_02026ee0.c`; line(s) 35, 68, 70.
- `eu/src/calls/InitSaveSystem.c` → `src/arm9/shared_engine/InitSaveSystem_02026dc0.c`; line(s) 13, 39, 55, 56, 59, 60, 66.
- `eu/src/calls/InvokeCallback.c` → `src/arm9/unclassified_helpers/func_020271e8.c`; line(s) 8, 12.
- `eu/src/calls/IsGlobalPackedBitSet.c` → `src/arm9/packed_bits/IsGlobalPackedBitSet_02027304.c`; line(s) 8, 13.
- `eu/src/calls/OnCardBackupUnlockDone.c` → `src/arm9/shared_engine/OnCardBackupUnlockDone_020270e0.c`; line(s) 8, 19, 22.
- `eu/src/calls/PollCardThreadResult.c` → `src/arm9/shared_engine/PollCardThreadResult_02027060.c`; line(s) 17, 37, 45, 47, 49, 50, 54, 55.
- `eu/src/calls/PollCardThreadState.c` → `src/arm9/shared_engine/PollCardThreadState_020271f8.c`; line(s) 13, 25, 26, 27, 31, 32, 33, 37, 38.
- `eu/src/calls/PollCardTransferThread.c` → `src/arm9/shared_engine/PollCardTransferThread_02026c3c.c`; line(s) 13, 21, 22, 23, 24, 25.
- `eu/src/calls/ReadCardBackupSync.c` → `src/arm9/shared_engine/ReadCardBackupSync_02026b00.c`; line(s) 8, 16.
- `eu/src/calls/ReadGlobalPackedBits.c` → `src/arm9/packed_bits/ReadGlobalPackedBits_02027348.c`; line(s) 8, 13.
- `eu/src/calls/SetCardThreadDoneCallback.c`; line(s) 5.
- `eu/src/calls/SetCardThreadDoneCallback_02026b04.c` → `src/arm9/shared_engine/SetCardThreadDoneCallback_02026af0.c`; line(s) 8, 13.
- `eu/src/calls/SetCardThreadStartTick.c` → `src/arm9/shared_engine/SetCardThreadStartTick_02027258.c`; line(s) 8, 13.
- `eu/src/calls/SetGlobalPackedBit.c` → `src/arm9/packed_bits/SetGlobalPackedBit_02027320.c`; line(s) 8, 13.
- `eu/src/calls/SetSharedFlagBits.c` → `src/arm9/unclassified_helpers/func_0202761c.c`; line(s) 8, 24.
- `eu/src/calls/StartCardTransferThread.c` → `src/arm9/shared_engine/StartCardTransferThread_02026be0.c`; line(s) 16, 25, 26, 27, 28, 29, 30, 31.
- `eu/src/calls/StartCardWriteFromSlot.c` → `src/arm9/shared_engine/StartCardWriteFromSlot_02027034.c`; line(s) 10, 17, 18, 20, 21.
- `eu/src/calls/TestRecordFlagBit.c`; line(s) 15, 33.
- `eu/src/calls/UpdateElapsedIntervals.c`; line(s) 31, 38.
- `eu/src/calls/WriteCardBackupSync.c` → `src/arm9/shared_engine/WriteCardBackupSync_02026b28.c`; line(s) 8, 16.
- `eu/src/calls/WriteCardSlotHeaders.c` → `src/arm9/shared_engine/WriteCardSlotHeaders_02027278.c`; line(s) 10, 25, 27, 29, 30, 32, 33, 34, 40.
- `eu/src/calls/WriteGlobalPackedBits.c` → `src/arm9/packed_bits/WriteGlobalPackedBits_02027360.c`; line(s) 8, 13.
- `eu/src/data/bss/Bss_main_0205fe00.c`; line(s) 4.

### `main:0205fe0c` → `gSaveIoStateDataTail`

Previous label `data_0205fe0c`; size **20 bytes**; source `eu/src/data/bss/Bss_main_0205fe00.c`.

20 BSS bytes continuing SaveIoState at offset 12: active-save-data pointer, completion callback, result word and 64-bit start tick.

InitSaveData sets the leading pointer to save-slot buffer +0x18 and clears 0x3760 payload bytes. SaveIoState.h proves the callback/result/tick offsets. BeginSaveSlotWrite reads the same pointer and start tick through the prefix-based whole view; many menu/field readers access the leading active-save pointer directly.

Limits: This native allocation is not a single pointer. Direct pointer declarations expose its first word only, while prefix-based views reach all 20 bytes. Keep the done callback and tick tail; do not merge or shrink the storage in this rename block.

Pinned references:

- `eu/src/calls/AcquireMapLayout.c` → `src/arm9/unclassified_helpers/AcquireMapLayout_020506dc.c`; line(s) 51, 90, 95.
- `eu/src/calls/AddRecordItem.c`; line(s) 38, 46.
- `eu/src/calls/AddSlotLevelProgress.c` → `src/arm9/record_management/AddSlotLevelProgress_0202900c.c`; line(s) 20, 39.
- `eu/src/calls/ApplyRecordMerge.c`; line(s) 41, 49, 61, 63.
- `eu/src/calls/ApplySelectionStatScaling.c` → `src/arm9/overlay_selection/ApplySelectionStatScaling_0204fbcc.c`; line(s) 23, 34.
- `eu/src/calls/ArmObject.c` → `src/arm9/shared_engine/ArmObject_0205115c.c`; line(s) 2, 4.
- `eu/src/calls/ArmObject_02051180.c` → `src/arm9/shared_engine/ArmObject_0205116c.c`; line(s) 2, 4.
- `eu/src/calls/BuildAbilityTable.c` → `src/arm9/unclassified_helpers/BuildAbilityTable_02050ea4.c`; line(s) 36, 51, 163, 167, 168.
- `eu/src/calls/BuildSelectionEntryList.c` → `src/arm9/overlay_selection/BuildSelectionEntryList_0204f98c.c`; line(s) 53, 72.
- `eu/src/calls/CanAllocateRecordSlot.c` → `src/arm9/record_management/CanAllocateRecordSlot_020291f8.c`; line(s) 3, 8.
- `eu/src/calls/ClearItemCountsByGroup.c` → `src/arm9/record_management/ClearItemCountsByGroup_0202987c.c`; line(s) 3, 7.
- `eu/src/calls/ComputePlayerStats.c` → `src/arm9/unclassified_helpers/ComputePlayerStats_02050b30.c`; line(s) 61, 162.
- `eu/src/calls/ComputeScaledPercentPlusOne.c` → `src/arm9/fixed_point/ComputeScaledPercentPlusOne_02051134.c`; line(s) 3, 8.
- `eu/src/calls/ConsumeSlotItemUse.c`; line(s) 28, 34, 39, 40.
- `eu/src/calls/CountUnlockedSlotsFx.c` → `src/arm9/shared_engine/CountUnlockedSlotsFx_02051200.c`; line(s) 4, 9.
- `eu/src/calls/DecrementByteCounter.c` → `src/arm9/record_management/DecrementByteCounter_02029370.c`; line(s) 3, 7.
- `eu/src/calls/FillSelectionRecordFromGroup.c` → `src/arm9/overlay_selection/FillSelectionRecordFromGroup_0204f8dc.c`; line(s) 28, 47.
- `eu/src/calls/FindSlotByActiveOrder.c` → `src/arm9/record_management/FindSlotByActiveOrder_0204f6dc.c`; line(s) 3, 16.
- `eu/src/calls/GetActiveRecordEntryOrNull.c` → `src/arm9/record_management/GetActiveRecordEntryOrNull_02029548.c`; line(s) 3, 13.
- `eu/src/calls/GetByteCounterOrDefault.c` → `src/arm9/record_management/GetByteCounterOrDefault_020291cc.c`; line(s) 4, 15.
- `eu/src/calls/GetDifficultyScale.c` → `src/arm9/shared_engine/GetDifficultyScale_0205117c.c`; line(s) 4, 8.
- `eu/src/calls/GetFlagTableValue.c` → `src/arm9/shared_engine/GetFlagTableValue_020511c4.c`; line(s) 8, 14.
- `eu/src/calls/GetUnlockedSlotValue.c` → `src/arm9/shared_engine/GetUnlockedSlotValue_02051270.c`; line(s) 15, 22.
- `eu/src/calls/GrantStarterRecordPair.c`; line(s) 32, 55, 59, 61, 62.
- `eu/src/calls/HalveForEachFlag.c` → `src/arm9/shared_engine/HalveForEachFlag_0205122c.c`; line(s) 4, 9.
- `eu/src/calls/InsertRecordEntry.c`; line(s) 45, 54.
- `eu/src/calls/MoveEquipmentSlot.c`; line(s) 43, 54.
- `eu/src/calls/RebuildRecordCounters.c` → `src/arm9/record_management/RebuildRecordCounters_02028e6c.c`; line(s) 35, 53, 54.
- `eu/src/calls/RefillSlotItemUses.c` → `src/arm9/record_management/RefillSlotItemUses_020294b8.c`; line(s) 26, 33, 37, 39, 41, 47.
- `eu/src/calls/RefreshFirstSelectionPlayerStats.c` → `src/arm9/reviewed_helpers/func_0204f840.c`; line(s) 3, 11.
- `eu/src/calls/RefreshSlotRecordCache.c` → `src/arm9/record_management/RefreshSlotRecordCache_02028f44.c`; line(s) 37, 62.
- `eu/src/calls/ReleaseRecordEntry.c` → `src/arm9/record_management/ReleaseRecordEntry_02029388.c`; line(s) 3, 24.
- `eu/src/calls/ResolveMergedRecordEntry.c` → `src/arm9/record_management/ResolveMergedRecordEntry_020295c8.c`; line(s) 3, 53, 63.
- `eu/src/calls/ResolveRecordHandle.c` → `src/arm9/record_management/ResolveRecordHandle_02029574.c`; line(s) 3, 25.
- `eu/src/calls/ScaleByKindAndMode.c` → `src/arm9/shared_engine/ScaleByKindAndMode_0204fd24.c`; line(s) 12, 17.
- `eu/src/calls/ScaleStatsByPercent.c` → `src/arm9/fixed_point/ScaleStatsByPercent_02050a80.c`; line(s) 11, 20.
- `eu/src/calls/SetupAllSelectionRecords.c` → `src/arm9/overlay_selection/SetupAllSelectionRecords_0204f85c.c`; line(s) 6, 18.
- `eu/src/calls/SyncSelectionRecordFromSlotEntry.c` → `src/arm9/overlay_selection/SyncSelectionRecordFromSlotEntry_0204fabc.c`; line(s) 21, 33.
- `eu/src/data/bss/Bss_main_0205fe00.c`; line(s) 3.
- `eu/src/overlays/ov001/calls/AddRegionProgress.c` → `src/ov001/shared_engine/AddRegionProgress_0206e074.c`; line(s) 28, 63.
- `eu/src/overlays/ov001/calls/ApplyPendingLevelUps.c` → `src/ov001/shared_engine/ApplyPendingLevelUps_0206ccd8.c`; line(s) 21, 30, 47.
- `eu/src/overlays/ov001/calls/AwardSlotLevelProgress.c`; line(s) 17, 47, 49, 50.
- `eu/src/overlays/ov001/calls/CaptureSaveSnapshot.c` → `src/ov001/unclassified_helpers/CaptureSaveSnapshot_02062eb4.c`; line(s) 46, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62.
- `eu/src/overlays/ov001/calls/CountFlaggedGroupEntries.c` → `src/ov001/unclassified_helpers/CountFlaggedGroupEntries_0208c3d0.c`; line(s) 8, 17.
- `eu/src/overlays/ov001/calls/EnterMenuItem.c` → `src/ov001/field_manager/EnterMenuItem_02067618.c`; line(s) 34, 51.
- `eu/src/overlays/ov001/calls/EnterSceneSlot.c` → `src/ov001/unclassified_helpers/EnterSceneSlot_020647a4.c`; line(s) 8, 20.
- `eu/src/overlays/ov001/calls/ExitSessionAndCommitSave.c`; line(s) 65, 107, 113, 114, 117.
- `eu/src/overlays/ov001/calls/FieldMenu_TryOpenByMode.c` → `src/ov001/field_manager/FieldMenu_TryOpenByMode_02077d64.c`; line(s) 37, 63.
- `eu/src/overlays/ov001/calls/GetSessionStateFlags2Bit.c` → `src/ov001/unclassified_helpers/GetSessionStateFlags2Bit_020649b8.c`; line(s) 8, 12.
- `eu/src/overlays/ov001/calls/InitFieldPanelScene.c`; line(s) 43, 84.
- `eu/src/overlays/ov001/calls/LoadDifficultyPresetIntoSession.c` → `src/ov001/unclassified_helpers/LoadDifficultyPresetIntoSession_020644d4.c`; line(s) 4, 17.
- `eu/src/overlays/ov001/calls/PlayWeightedRandomEntry.c` → `src/ov001/shared_engine/PlayWeightedRandomEntry_02069530.c`; line(s) 32, 51.
- `eu/src/overlays/ov001/calls/ProbeKnockbackStageTarget.c` → `src/ov001/shared_engine/ProbeKnockbackStageTarget_02096f38.c`; line(s) 83, 167.
- `eu/src/overlays/ov001/calls/ProbeStageObjectHit.c`; line(s) 96, 209.
- `eu/src/overlays/ov001/calls/RequestPanelModeChange.c` → `src/ov001/leaf_research/RequestPanelModeChange_0207b27c.c`; line(s) 26, 51.
- `eu/src/overlays/ov001/calls/RestoreSaveSnapshot.c` → `src/ov001/unclassified_helpers/RestoreSaveSnapshot_02062fa4.c`; line(s) 46, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65.
- `eu/src/overlays/ov001/calls/SaveSessionCheckpoint.c` → `src/ov001/unclassified_helpers/SaveSessionCheckpoint_02064364.c`; line(s) 48, 107.
- `eu/src/overlays/ov001/calls/ScheduleSpawnerNextTime.c` → `src/ov001/shared_engine/ScheduleSpawnerNextTime_02096928.c`; line(s) 38, 55.
- `eu/src/overlays/ov001/calls/StartFieldSession.c` → `src/ov001/field_manager/StartFieldSession_02061468.c`; line(s) 107, 240, 241, 279, 298, 305, 306, 318.
- `eu/src/overlays/ov001/calls/StoreSessionDifficultyPreset.c` → `src/ov001/unclassified_helpers/StoreSessionDifficultyPreset_0206452c.c`; line(s) 4, 16.
- `eu/src/overlays/ov001/calls/TriggerFieldMenuButtonRecords.c` → `src/ov001/field_manager/TriggerFieldMenuButtonRecords_020771a8.c`; line(s) 27, 42.
- `eu/src/overlays/ov001/calls/UpdateFieldMenuSelectionTags.c`; line(s) 15, 43.
- `eu/src/overlays/ov002/Ov002SaveData.h`; line(s) 13, 14.
- `eu/src/overlays/ov002/calls/ApplyGlobalMenuCategoryRecord.c`; line(s) 3, 7.
- `eu/src/overlays/ov002/calls/ApplySingleGlobalMenuRecord.c`; line(s) 3, 7.
- `eu/src/overlays/ov002/calls/ClearGlobalMenuRecordField.c`; line(s) 3, 7.
- `eu/src/overlays/ov002/calls/ClearGlobalMenuSecondaryRecordFlag.c`; line(s) 3, 7.
- `eu/src/overlays/ov002/calls/MarkGlobalMenuRecordFlagBits.c`; line(s) 3, 7.
- `eu/src/overlays/ov002/calls/UpdateSaveMenuState.c` → `src/ov002/panel_state/UpdateSaveMenuState.c`; line(s) 13, 83.
- `eu/src/overlays/ov021/calls/ApplyRewardByTier.c` → `src/ov021/reviewed_helpers/ApplyRewardByTier_020a7a40.c`; line(s) 18, 103.
- `eu/src/overlays/ov021/calls/ToggleFieldButtonFlags.c` → `src/ov021/unclassified_helpers/ToggleFieldButtonFlags_020a6fd8.c`; line(s) 30, 47.
- `eu/src/overlays/ov021/calls/UpdateFieldButtonInput.c` → `src/ov021/unclassified_helpers/UpdateFieldButtonInput_020a70a8.c`; line(s) 34, 76, 89, 94, 143, 144, 150.
- `eu/src/overlays/ov024/calls/PlaceBoardBonuses.c` → `src/ov024/board_setup/PlaceBoardBonuses_020b61ec.c`; line(s) 32, 82.
- `eu/src/overlays/ov033/calls/BeginResumeMode.c`; line(s) 15, 33.
- `eu/src/overlays/ov034/calls/CloseResultsSession.c`; line(s) 29, 69.
- `eu/src/overlays/ov034/calls/HandleResultsInput.c`; line(s) 97, 375, 381, 387, 388, 389.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; line(s) 203, 373.
- `eu/src/overlays/ov038/calls/BuildCompletionStats.c`; line(s) 36, 215.
- `eu/src/overlays/ov039/calls/FormatSaveLocationLabel.c`; line(s) 10, 40.
- `eu/src/overlays/ov041/calls/HandleCommandMenuShortcuts.c`; line(s) 21, 44.
- `eu/src/overlays/ov042/calls/ApplyCameraConfig.c` → `src/ov042/camera/ApplyCameraConfig_020be4ac.c`; line(s) 23, 30, 34, 41, 44.
- `eu/src/overlays/ov045/calls/RunResultTallyStep.c`; line(s) 100, 235, 310, 313.
- `eu/src/overlays/ov046/calls/Camera_LoadOptionFlags.c` → `src/ov046/shared_engine/Camera_LoadOptionFlags_020c2ae0.c`; line(s) 20, 29, 33, 40, 43.
- `eu/src/overlays/ov046/calls/Camera_SetFollowSuspended.c` → `src/ov046/shared_engine/Camera_SetFollowSuspended_020c29c0.c`; line(s) 27, 39.
- `eu/src/overlays/ov047/calls/Camera_ShouldStartManualTurn.c` → `src/ov047/camera/Camera_ShouldStartManualTurn_020c3ad8.c`; line(s) 15, 26.
- `eu/src/overlays/ov047/calls/Camera_TurnToLeaderHeading.c` → `src/ov047/camera/Camera_TurnToLeaderHeading_020c4e3c.c`; line(s) 87, 128.
- `eu/src/overlays/ov047/calls/Camera_UpdateFollowInput.c` → `src/ov047/camera/Camera_UpdateFollowInput_020c3b5c.c`; line(s) 84, 413.
- `eu/src/overlays/ov047/calls/Camera_UpdateManualTurn.c` → `src/ov047/camera/Camera_UpdateManualTurn_020c4668.c`; line(s) 67, 92.
- `eu/src/overlays/ov052/calls/ComputeApproachStep.c` → `src/ov052/actor_motion/ComputeApproachStep_020cc2f0.c`; line(s) 75, 119.
- `eu/src/overlays/ov052/calls/TryLedgeClimb.c`; line(s) 116, 214.
- `eu/src/overlays/ov059/calls/Actor_UpdateGroundMove.c`; line(s) 56, 186.
- `eu/src/overlays/ov059/calls/Actor_UpdateJump.c` → `src/ov059/unclassified_helpers/Actor_UpdateJump_020ca33c.c`; line(s) 49, 96.
- `eu/src/overlays/ov073/calls/DestroyStatusMenu.c`; line(s) 4, 33.
- `eu/src/overlays/ov073/calls/DrawRecordSlotRows.c` → `src/ov073/status_menu/DrawRecordSlotRows_020c06f0.c`; line(s) 78, 174, 288.
- `eu/src/overlays/ov073/calls/FixSelectedSlotIndex.c` → `src/ov073/status_menu/FixSelectedSlotIndex_020c026c.c`; line(s) 20, 27, 38, 39.
- `eu/src/overlays/ov073/calls/GetPlayerLevelTier.c` → `src/ov073/status_menu/GetPlayerLevelTier_020c1418.c`; line(s) 17, 27.
- `eu/src/overlays/ov073/calls/HandleSlotListInput.c` → `src/ov073/status_menu/HandleSlotListInput_020c032c.c`; line(s) 56, 127, 129, 168, 191.
- `eu/src/overlays/ov073/calls/InitStatusMenu.c`; line(s) 103, 304, 305, 360, 366, 368, 372.
- `eu/src/overlays/ov073/calls/MoveSummarySlot.c` → `src/ov073/status_menu/MoveSummarySlot_020bebd0.c`; line(s) 26, 47.
- `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c`; line(s) 174, 229, 354, 363, 364, 385, 411.
- `eu/src/overlays/ov073/calls/ShowStatusPageContents.c` → `src/ov073/status_menu/ShowStatusPageContents_020c1b28.c`; line(s) 30, 59.
- `eu/src/overlays/ov073/calls/UpdateSlotFillCounts.c`; line(s) 15, 22, 30.
- `eu/src/overlays/ov074/calls/InitRootMenu.c` → `src/ov074/root_menu/InitRootMenu_020c4260.c`; line(s) 125, 289, 326, 489.
- `eu/src/overlays/ov075/calls/ApplyLevelRankParam.c` → `src/ov075/unclassified_helpers/ApplyLevelRankParam_020ce730.c`; line(s) 23, 43.
- `eu/src/overlays/ov075/calls/BuildRecordCountList.c` → `src/ov075/unclassified_helpers/BuildRecordCountList_020ccd58.c`; line(s) 47, 139, 140, 145, 180, 183, 192, 196, 201.
- `eu/src/overlays/ov075/calls/CloseItemPicker.c` → `src/ov075/unclassified_helpers/CloseItemPicker_020cde4c.c`; line(s) 25, 55.
- `eu/src/overlays/ov075/calls/CommitOptionChoice.c` → `src/ov075/unclassified_helpers/CommitOptionChoice_020c6358.c`; line(s) 42, 57, 60, 64, 70, 76, 82.
- `eu/src/overlays/ov075/calls/ConsumeItemPickerSelectionAndApplyReward.c`; line(s) 35, 60, 71.
- `eu/src/overlays/ov075/calls/CycleNodeCategory.c` → `src/ov075/unclassified_helpers/CycleNodeCategory_020cbb34.c`; line(s) 47, 76.
- `eu/src/overlays/ov075/calls/DrawMatrixCellGlyph.c`; line(s) 19, 56.
- `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`; line(s) 193, 227, 232, 251, 423, 633.
- `eu/src/overlays/ov075/calls/FindNearestReachableNode.c` → `src/ov075/unclassified_helpers/FindNearestReachableNode_020c8eac.c`; line(s) 23, 48.
- `eu/src/overlays/ov075/calls/GetNodeGroupIfUnlocked.c` → `src/ov075/unclassified_helpers/GetNodeGroupIfUnlocked_020c6080.c`; line(s) 31, 43.
- `eu/src/overlays/ov075/calls/GetOptionChangeNotice.c` → `src/ov075/unclassified_helpers/GetOptionChangeNotice_020c6134.c`; line(s) 27, 63, 64, 67, 79, 83.
- `eu/src/overlays/ov075/calls/HasPendingUnlocks.c` → `src/ov075/unclassified_helpers/HasPendingUnlocks_020c49a8.c`; line(s) 8, 15.
- `eu/src/overlays/ov075/calls/InitMatrixMenu.c` → `src/ov075/matrix_menu/InitMatrixMenu_020c49cc.c`; line(s) 185, 291, 486, 491, 492, 546, 552, 554, 578.
- `eu/src/overlays/ov075/calls/IsMenuModeUnlocked.c` → `src/ov075/unclassified_helpers/IsMenuModeUnlocked_020c4324.c`; line(s) 8, 12.
- `eu/src/overlays/ov075/calls/IsRewardEntryLocked.c` → `src/ov075/unclassified_helpers/IsRewardEntryLocked_020ced28.c`; line(s) 28, 40.
- `eu/src/overlays/ov075/calls/JumpCursorToEntry.c` → `src/ov075/unclassified_helpers/JumpCursorToEntry_020cae58.c`; line(s) 34, 57, 62.
- `eu/src/overlays/ov075/calls/MenuPanel_DrawItemRows_020d076c.c` → `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`; line(s) 111, 132, 150, 216.
- `eu/src/overlays/ov075/calls/MoveMatrixCursorDown_020cb178.c` → `src/ov075/matrix_menu/MoveMatrixCursorDown_020cb178.c`; line(s) 56, 101, 106.
- `eu/src/overlays/ov075/calls/MoveMatrixCursorLeft_020cb410.c` → `src/ov075/matrix_menu/MoveMatrixCursorLeft_020cb410.c`; line(s) 57, 113, 118.
- `eu/src/overlays/ov075/calls/MoveMatrixCursorRight.c` → `src/ov075/matrix_menu/MoveMatrixCursorRight_020cb658.c`; line(s) 57, 117, 122.
- `eu/src/overlays/ov075/calls/MoveMatrixCursorUp_020caf38.c` → `src/ov075/matrix_menu/MoveMatrixCursorUp_020caf38.c`; line(s) 56, 101, 106.
- `eu/src/overlays/ov075/calls/OnMessageDialogClosed.c` → `src/ov075/unclassified_helpers/OnMessageDialogClosed_020c8d30.c`; line(s) 20, 49.
- `eu/src/overlays/ov075/calls/PreviewMatrixNodeStats_020c5d10.c` → `src/ov075/matrix_menu/PreviewMatrixNodeStats_020c5d10.c`; line(s) 35, 74, 138, 154, 155.
- `eu/src/overlays/ov075/calls/PropagateMatrixNodeVisit.c`; line(s) 55, 65, 97, 100, 101, 116, 119, 120, 144, 152, 246.
- `eu/src/overlays/ov075/calls/ResolveGridEntry.c` → `src/ov075/unclassified_helpers/ResolveGridEntry_020c8dfc.c`; line(s) 19, 39, 52.
- `eu/src/overlays/ov075/calls/SelectLinkedMatrixNode.c`; line(s) 48, 82, 86.
- `eu/src/overlays/ov075/calls/SelectMatrixNode.c` → `src/ov075/matrix_menu/SelectMatrixNode_020c4370.c`; line(s) 95, 128, 188, 217, 219.
- `eu/src/overlays/ov075/calls/ShowEntryHeaderMessage.c` → `src/ov075/unclassified_helpers/ShowEntryHeaderMessage_020cad14.c`; line(s) 52, 143.
- `eu/src/overlays/ov075/calls/ShowNextUnlockNotice.c` → `src/ov075/unclassified_helpers/ShowNextUnlockNotice_020cc9fc.c`; line(s) 56, 68, 117, 124, 131.
- `eu/src/overlays/ov075/calls/ShutdownMatrixMenu.c` → `src/ov075/unclassified_helpers/ShutdownMatrixMenu_020c7de8.c`; line(s) 8, 39, 63, 67.
- `eu/src/overlays/ov075/calls/TracePipePath.c` → `src/ov075/unclassified_helpers/TracePipePath_020caa98.c`; line(s) 27, 73, 74.
- `eu/src/overlays/ov075/calls/TryCompleteGridGroup.c` → `src/ov075/unclassified_helpers/TryCompleteGridGroup_020c5fac.c`; line(s) 34, 56, 63.
- `eu/src/overlays/ov075/calls/UnlockableListPanel_Open.c` → `src/ov075/unclassified_helpers/func_ov075_020d0014.c`; line(s) 100, 187.
- `eu/src/overlays/ov075/calls/UpdateMatrixEventAnimation.c`; line(s) 100, 139, 140, 291, 422, 436, 437, 438.
- `eu/src/overlays/ov075/calls/UpdateMatrixMenu.c` → `src/ov075/matrix_menu/UpdateMatrixMenu_020c707c.c`; line(s) 201, 265, 426, 563, 615.
- `eu/src/overlays/ov075/calls/UpdateMatrixOptionMenu.c`; line(s) 147, 344, 351, 390, 419.
- `eu/src/overlays/ov076/calls/ApplySlotMenuThresholdRankBonus.c`; line(s) 23, 43.
- `eu/src/overlays/ov076/calls/ItemList_BuildStock.c` → `src/ov076/unclassified_helpers/ItemList_BuildStock_020c8fa0.c`; line(s) 52, 60, 137, 138, 181, 184, 194, 198, 203.
- `eu/src/overlays/ov076/calls/ItemList_IsRewardEntryLocked.c` → `src/ov076/unclassified_helpers/ItemList_IsRewardEntryLocked_020cab38.c`; line(s) 28, 40.
- `eu/src/overlays/ov076/calls/ItemList_ReturnCursorItem.c` → `src/ov076/unclassified_helpers/ItemList_ReturnCursorItem_020ca6f8.c`; line(s) 35, 60, 71.
- `eu/src/overlays/ov076/calls/ItemSelectionPanel_Open.c` → `src/ov076/unclassified_helpers/MenuPanel_Open_020cc0e4.c`; line(s) 100, 187.
- `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`; line(s) 111, 132, 150, 216.
- `eu/src/overlays/ov076/calls/SlotMenu_BuildSlotMasks.c` → `src/ov076/unclassified_helpers/SlotMenu_BuildSlotMasks_020c4260.c`; line(s) 21, 35, 47, 48.
- `eu/src/overlays/ov076/calls/SlotMenu_CanCombineSlotPair.c` → `src/ov076/unclassified_helpers/SlotMenu_CanCombineSlotPair_020c44c0.c`; line(s) 22, 29, 30.
- `eu/src/overlays/ov076/calls/SlotMenu_CloseItemList.c`; line(s) 23, 53.
- `eu/src/overlays/ov076/calls/SlotMenu_DrawPanelLabel.c` → `src/ov076/unclassified_helpers/SlotMenu_DrawPanelLabel_020c7edc.c`; line(s) 31, 118.
- `eu/src/overlays/ov076/calls/SlotMenu_DrawSlotModels_020c7708.c` → `src/ov076/matrix_menu/SlotMenu_DrawSlotModels_020c7708.c`; line(s) 47, 91, 98, 112, 130, 131.
- `eu/src/overlays/ov076/calls/SlotMenu_EquipRecordEntry.c`; line(s) 26, 41.
- `eu/src/overlays/ov076/calls/SlotMenu_EquipSlotEntry.c`; line(s) 23, 33, 40.
- `eu/src/overlays/ov076/calls/SlotMenu_FuseSlotRecords.c` → `src/ov076/unclassified_helpers/SlotMenu_FuseSlotRecords_020c851c.c`; line(s) 41, 55, 84, 86.
- `eu/src/overlays/ov076/calls/SlotMenu_GetSlotFillState.c` → `src/ov076/unclassified_helpers/SlotMenu_GetSlotFillState_020c4764.c`; line(s) 8, 20, 29, 31.
- `eu/src/overlays/ov076/calls/SlotMenu_HandleColumnInput.c` → `src/ov076/unclassified_helpers/SlotMenu_HandleColumnInput_020c4894.c`; line(s) 25, 63, 74, 82, 117.
- `eu/src/overlays/ov076/calls/SlotMenu_HasFullyRankedSlot.c` → `src/ov076/unclassified_helpers/SlotMenu_HasFullyRankedSlot_020c503c.c`; line(s) 21, 36, 40, 41.
- `eu/src/overlays/ov076/calls/SlotMenu_HasThreeFilledSlotsAndFlags.c` → `src/ov076/unclassified_helpers/SlotMenu_HasThreeFilledSlotsAndFlags_020c5248.c`; line(s) 13, 18.
- `eu/src/overlays/ov076/calls/SlotMenu_HasUnpairedSlotAndStock.c`; line(s) 21, 54.
- `eu/src/overlays/ov076/calls/SlotMenu_Init.c` → `src/ov076/unclassified_helpers/SlotMenu_Init_020c45a8.c`; line(s) 55, 100.
- `eu/src/overlays/ov076/calls/SlotMenu_InitTouchLayout.c` → `src/ov076/unclassified_helpers/SlotMenu_InitTouchLayout_020c63b4.c`; line(s) 27, 36.
- `eu/src/overlays/ov076/calls/SlotMenu_IsSelectedRecordEquipped.c`; line(s) 25, 46.
- `eu/src/overlays/ov076/calls/SlotMenu_IsSlotPairFilled.c` → `src/ov076/unclassified_helpers/SlotMenu_IsSlotPairFilled_020c4560.c`; line(s) 8, 13, 14.
- `eu/src/overlays/ov076/calls/SlotMenu_LoadCursorSlotRecord.c` → `src/ov076/unclassified_helpers/SlotMenu_LoadCursorSlotRecord_020c4444.c`; line(s) 27, 43.
- `eu/src/overlays/ov076/calls/SlotMenu_OpenEmptySlot.c` → `src/ov076/unclassified_helpers/SlotMenu_OpenEmptySlot_020c4f7c.c`; line(s) 15, 33.
- `eu/src/overlays/ov076/calls/SlotMenu_ReloadSlot.c` → `src/ov076/unclassified_helpers/SlotMenu_ReloadSlot_020c6f60.c`; line(s) 47, 92, 99, 126.
- `eu/src/overlays/ov076/calls/SlotMenu_ReloadVisibleSlots.c` → `src/ov076/unclassified_helpers/SlotMenu_ReloadVisibleSlots_020c7144.c`; line(s) 13, 18.
- `eu/src/overlays/ov076/calls/SlotMenu_ShowSlotHint.c` → `src/ov076/unclassified_helpers/SlotMenu_ShowSlotHint_020c827c.c`; line(s) 21, 40.
- `eu/src/overlays/ov076/calls/SlotMenu_ToggleStockInSlot.c` → `src/ov076/unclassified_helpers/SlotMenu_ToggleStockInSlot_020c4a90.c`; line(s) 34, 46.
- `eu/src/overlays/ov076/calls/SlotMenu_UnequipCursorSlot.c` → `src/ov076/unclassified_helpers/SlotMenu_UnequipCursorSlot_020c8d70.c`; line(s) 22, 45.
- `eu/src/overlays/ov076/calls/SlotMenu_UnequipSlotEntry.c` → `src/ov076/unclassified_helpers/SlotMenu_UnequipSlotEntry_020c89e0.c`; line(s) 26, 33, 43, 44, 47.
- `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c` → `src/ov076/unclassified_helpers/SlotMenu_UpdateEditScreen_020c546c.c`; line(s) 95, 268, 273, 287, 387, 388, 393, 394, 396, 401, 402.
- `eu/src/overlays/ov076/calls/SlotMenu_UpdatePairedCategory.c` → `src/ov076/unclassified_helpers/SlotMenu_UpdatePairedCategory_020c53c8.c`; line(s) 31, 37.
- `eu/src/overlays/ov076/calls/SlotMenu_UpdateStatusHeader.c`; line(s) 50, 64, 72.
- `eu/src/overlays/ov077/calls/ApplyItemScreenThresholdRankBonus.c`; line(s) 23, 43.
- `eu/src/overlays/ov077/calls/AssignCursorItemToPartySlot.c` → `src/ov077/unclassified_helpers/AssignCursorItemToPartySlot_020c4598.c`; line(s) 53, 72, 74, 76, 77, 87, 90, 93, 95, 96.
- `eu/src/overlays/ov077/calls/BeginSlotItemSelection.c` → `src/ov077/unclassified_helpers/BeginSlotItemSelection_020c5cc8.c`; line(s) 27, 62, 65, 68.
- `eu/src/overlays/ov077/calls/CanUseItemEntry.c` → `src/ov077/unclassified_helpers/CanUseItemEntry_020c7b6c.c`; line(s) 28, 41.
- `eu/src/overlays/ov077/calls/DrawPartySlotIcons.c` → `src/ov077/unclassified_helpers/DrawPartySlotIcons_020c56f4.c`; line(s) 26, 33, 35, 37, 38.
- `eu/src/overlays/ov077/calls/DrawPartySlotLabel.c` → `src/ov077/unclassified_helpers/DrawPartySlotLabel_020c5a4c.c`; line(s) 32, 49, 51, 53, 54.
- `eu/src/overlays/ov077/calls/HandleItemTabTouch.c` → `src/ov077/unclassified_helpers/HandleItemTabTouch_020c43f8.c`; line(s) 22, 36.
- `eu/src/overlays/ov077/calls/InitItemListEntries.c` → `src/ov077/unclassified_helpers/InitItemListEntries_020c5fd4.c`; line(s) 47, 84, 97, 132, 135, 144, 148, 153.
- `eu/src/overlays/ov077/calls/InitItemScreen.c`; line(s) 73, 116.
- `eu/src/overlays/ov077/calls/ItemListPanel_Open.c` → `src/ov077/unclassified_helpers/MenuPanel_Open_020c9118.c`; line(s) 100, 187.
- `eu/src/overlays/ov077/calls/ItemList_ReturnCursorItem_020c774c.c` → `src/ov077/unclassified_helpers/ItemList_ReturnCursorItem_020c772c.c`; line(s) 35, 60, 71.
- `eu/src/overlays/ov077/calls/ItemMenu_CloseItemList.c`; line(s) 23, 53.
- `eu/src/overlays/ov077/calls/MenuPanel_DrawItemRows_020c9870.c` → `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`; line(s) 111, 132, 150, 216.
- `eu/src/overlays/ov077/calls/MoveSlotCursor.c` → `src/ov077/unclassified_helpers/MoveSlotCursor_020c4514.c`; line(s) 21, 37.
- `eu/src/overlays/ov077/calls/SetupItemScreenBackgrounds.c` → `src/ov077/unclassified_helpers/SetupItemScreenBackgrounds_020c4dd4.c`; line(s) 37, 53.
- `eu/src/overlays/ov077/calls/ShowSlotHeaderMessage.c` → `src/ov077/unclassified_helpers/ShowSlotHeaderMessage_020c58e0.c`; line(s) 14, 23.
- `eu/src/overlays/ov077/calls/ShowSlotItemHeader.c` → `src/ov077/unclassified_helpers/ShowSlotItemHeader_020c437c.c`; line(s) 27, 34, 36, 38, 39.
- `eu/src/overlays/ov077/calls/UpdateItemCountDigits.c` → `src/ov077/unclassified_helpers/UpdateItemCountDigits_020c52a0.c`; line(s) 37, 50, 55.
- `eu/src/overlays/ov077/calls/UpdateItemScreen.c` → `src/ov077/unclassified_helpers/UpdateItemScreen_020c477c.c`; line(s) 72, 111, 113, 115, 116.
- `eu/src/overlays/ov077/calls/UpdateItemScreenStatusLink.c` → `src/ov077/unclassified_helpers/UpdateItemScreenStatusLink_020c53a0.c`; line(s) 62, 81, 83, 85, 86.
- `eu/src/overlays/ov077/calls/UsePartySlotItem.c` → `src/ov077/unclassified_helpers/UsePartySlotItem_020c5dd8.c`; line(s) 37, 49, 51, 53, 54, 64, 67, 70, 72, 73, 100.
- `eu/src/overlays/ov078/calls/InitPageMenu.c` → `src/ov078/unclassified_helpers/InitPageMenu_020c4260.c`; line(s) 29, 64, 65.
- `eu/src/overlays/ov078/calls/SetupPageMenuBackgrounds.c`; line(s) 35, 148.
- `eu/src/overlays/ov079/calls/ConfigMenu_CreateOption.c`; line(s) 6, 19.
- `eu/src/overlays/ov079/calls/ConfigMenu_Init.c`; line(s) 73, 115.
- `eu/src/overlays/ov079/calls/ConfigMenu_SaveOptions.c` → `src/ov079/unclassified_helpers/ConfigMenu_SaveOptions_020c4800.c`; line(s) 45, 59.
- `eu/src/overlays/ov080/calls/BuildSlotSummary.c` → `src/ov080/unclassified_helpers/BuildSlotSummary_020c4b84.c`; line(s) 38, 55, 61, 62, 77.
- `eu/src/overlays/ov080/calls/ConfirmSaveSelectStep.c` → `src/ov080/unclassified_helpers/ConfirmSaveSelectStep_020c5a0c.c`; line(s) 41, 95.
- `eu/src/overlays/ov080/calls/DestroySaveSelectScreen.c` → `src/ov080/unclassified_helpers/DestroySaveSelectScreen_020c4ad0.c`; line(s) 25, 56, 58.
- `eu/src/overlays/ov080/calls/HandleSlotReadResult.c` → `src/ov080/unclassified_helpers/HandleSlotReadResult_020c4cb8.c`; line(s) 17, 25.
- `eu/src/overlays/ov080/calls/InitSaveSelectScreen.c` → `src/ov080/unclassified_helpers/InitSaveSelectScreen_020c42b0.c`; line(s) 89, 181, 245.
- `eu/src/overlays/ov080/calls/LoadSlotIntoGame.c` → `src/ov080/unclassified_helpers/LoadSlotIntoGame_020c58c4.c`; line(s) 10, 29, 33.
- `eu/src/overlays/ov080/calls/PollSaveSlotReads.c`; line(s) 31, 92, 96, 97, 101.
- `eu/src/overlays/ov080/calls/UpdateSaveSelectScreen.c` → `src/ov080/unclassified_helpers/UpdateSaveSelectScreen_020c4740.c`; line(s) 58, 126, 188, 201, 207.
- `eu/src/overlays/ov082/calls/SetupOv082Screen.c` → `src/ov082/unclassified_helpers/SetupOv082Screen_020beb48.c`; line(s) 56, 162.
- `eu/src/overlays/ov083/calls/ApplyScoreEvents.c` → `src/ov083/unclassified_helpers/ApplyScoreEvents_020bf388.c`; line(s) 41, 50.
- `eu/src/overlays/ov083/calls/InitScoreScreen.c`; line(s) 86, 171, 172, 216.
- `eu/src/overlays/ov083/calls/UpdateScoreScreen.c` → `src/ov083/unclassified_helpers/UpdateScoreScreen_020bef1c.c`; line(s) 48, 85.
- `eu/src/overlays/ov084/calls/InitSelectMenu.c` → `src/ov084/select_menu/InitSelectMenu_020bf700.c`; line(s) 59, 130.
- `eu/src/overlays/ov085/calls/BuildRecordCountList_020c1994.c` → `src/ov085/unclassified_helpers/BuildRecordCountList_020c1974.c`; line(s) 47, 139, 140, 145, 180, 183, 192, 196, 201.
- `eu/src/overlays/ov085/calls/CanSelectItem.c` → `src/ov085/unclassified_helpers/CanSelectItem_020c138c.c`; line(s) 30, 55.
- `eu/src/overlays/ov085/calls/ConfirmItemMenuChoice.c` → `src/ov085/unclassified_helpers/ConfirmItemMenuChoice_020c168c.c`; line(s) 53, 115.
- `eu/src/overlays/ov085/calls/InitShopMenu.c` → `src/ov085/unclassified_helpers/InitShopMenu_020bf7f0.c`; line(s) 100, 191, 347, 377, 379.
- `eu/src/overlays/ov085/calls/RedrawShopMenu.c`; line(s) 105, 158, 326.
- `eu/src/overlays/ov085/calls/SetShopMenuMode.c` → `src/ov085/unclassified_helpers/SetShopMenuMode_020c0b90.c`; line(s) 107, 195, 198, 213, 297, 298, 300, 304, 322, 324, 340.
- `eu/src/overlays/ov086/calls/CountGroupFlaggedEntries_020bf4a4.c` → `src/ov086/panel_state/CountGroupFlaggedEntries_020bf484.c`; line(s) 9, 33.
- `eu/src/overlays/ov086/calls/InitRecordPanelDigits.c` → `src/ov086/panel_state/InitRecordPanelDigits_020c1ba8.c`; line(s) 22, 52.
- `eu/src/overlays/ov086/calls/UpdateRecordPanelInput.c` → `src/ov086/panel_state/UpdateRecordPanelInput_020c1ed4.c`; line(s) 16, 61.
- `eu/src/overlays/ov089/calls/DrawEntryMenuTexts_020bf49c.c`; line(s) 43, 80, 90.

### `main:0205fe20` → `gSaveSlotMenuEntryEnabled`

Previous label `data_0205fe20`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205fe20.c`.

4 BSS bytes used as a normalized 0/1 menu-availability flag.

ApplyPanelMenuFlags clears it when usedSlotCount is zero and sets it otherwise. CountValidSlots also stores whether either save-slot status is nonzero. BuildMenuEntryList includes menu entry 1 only when this flag is nonzero.

Limits: Nonzero status includes status 1 from a read error, while PollSaveSlotReads separately tests status >=2 for selecting valid save stamps. This name does not claim that the flag proves a successfully validated save or a completed I/O operation.

Pinned references:

- `eu/src/data/bss/Bss_main_0205fe20.c`; line(s) 3.
- `eu/src/overlays/ov000/calls/ApplyPanelMenuFlags.c` → `src/ov000/panel_state/ApplyPanelMenuFlags_02061bf4.c`; line(s) 14, 29, 39.
- `eu/src/overlays/ov037/calls/BuildMenuEntryList.c` → `src/ov037/unclassified_helpers/BuildMenuEntryList_020bb314.c`; line(s) 17, 28.
- `eu/src/overlays/ov080/calls/CountValidSlots.c` → `src/ov080/unclassified_helpers/CountValidSlots_020c4260.c`; line(s) 16, 26.

### `main:0205fec4` → `gRuntimeRecordCategoryCounters`

Previous label `data_0205fec4`; size **256 bytes**; source `eu/src/data/bss/Bss_main_0205febc.c`.

256 BSS bytes: 128 category halfword counters. Native total/capacity halfwords and the slot-cache area follow in separate allocations.

RebuildRecordCounters zeroes the larger logical counter/cache view and increments categoryCounts[entry->category] for active records. AddRecordItem and ReleaseRecordEntry update the corresponding category count; CanAllocateRecordSlot reads the following total/capacity halfwords through the same base.

Limits: Keep the native 256-byte allocation. Existing declarations sometimes expose a larger RecordCounters or RecordCounterStorage view; the name does not imply those trailing fields are part of this ELF symbol or that the halfword count is an inventory capacity.

Pinned references:

- `eu/src/calls/AddRecordItem.c`; line(s) 39, 54, 58.
- `eu/src/calls/ApplyRecordMerge.c`; line(s) 42, 50, 65.
- `eu/src/calls/CanAllocateRecordSlot.c` → `src/arm9/record_management/CanAllocateRecordSlot_020291f8.c`; line(s) 4, 13.
- `eu/src/calls/GetByteCounterOrDefault.c` → `src/arm9/record_management/GetByteCounterOrDefault_020291cc.c`; line(s) 3, 11.
- `eu/src/calls/InsertRecordEntry.c`; line(s) 46, 55, 58, 65.
- `eu/src/calls/RebuildRecordCounters.c` → `src/arm9/record_management/RebuildRecordCounters_02028e6c.c`; line(s) 36, 55.
- `eu/src/calls/RefreshSlotRecordCache.c` → `src/arm9/record_management/RefreshSlotRecordCache_02028f44.c`; line(s) 38, 50.
- `eu/src/calls/ReleaseRecordEntry.c` → `src/arm9/record_management/ReleaseRecordEntry_02029388.c`; line(s) 4, 27.
- `eu/src/data/bss/Bss_main_0205febc.c`; line(s) 3.

### `main:02060570` → `gTextureUploadCallback`

Previous label `data_02060570`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02060570.c`.

4 BSS bytes holding a native function pointer with arguments (source, destination offset, byte count).

Tex_LoadVram invokes this callback for regular texture data and compressed 4x4 texture/index data. AttachPendingSceneModel and SwapActorSlotResource explicitly assign LoadTextureInChunks before using their model resources.

Limits: This is a global dispatch slot, not an owned texture buffer. The observed writers can refer to overlay code; callback lifetime and initialization before other callers remain the native caller responsibility.

Pinned references:

- `eu/src/calls/Tex_LoadVram.c` → `src/arm9/shared_engine/Tex_LoadVram_0202d14c.c`; line(s) 28, 40, 49, 50.
- `eu/src/data/bss/Bss_main_02060570.c`; line(s) 7.
- `eu/src/overlays/ov036/calls/AttachPendingSceneModel.c` → `src/ov036/unclassified_helpers/AttachPendingSceneModel_020bd130.c`; line(s) 24, 34.
- `eu/src/overlays/ov036/calls/SwapActorSlotResource.c` → `src/ov036/unclassified_helpers/SwapActorSlotResource_020bc978.c`; line(s) 37, 55.

### `main:0206076c` → `gMatrixCaptureSceneNode`

Previous label `data_0206076c`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0206076c.c`.

4 BSS bytes holding the scene-node pointer consulted by node-matrix capture.

SceneNode_Draw assigns node to this slot only when node->child is non-NULL, before NNS_G3dDraw. CaptureTrackedNodeMatrixCallback walks that owner's linked captures and copies the current matrix into a matching node ID.

Limits: The drawing function neither clears nor restores this slot on return or for a childless node. Do not treat it as a stack-scoped current-node binding or assume reentrant rendering is supported.

Pinned references:

- `eu/src/calls/CaptureTrackedNodeMatrixCallback.c` → `src/arm9/model_animation/CaptureTrackedNodeMatrixCallback_0202f13c.c`; line(s) 27, 36.
- `eu/src/calls/SceneNode_Draw.c`; line(s) 41, 79.
- `eu/src/data/bss/Bss_main_0206076c.c`; line(s) 4.

### `main:02060770` → `gChildNodeNameScratch`

Previous label `data_02060770`; size **16 bytes**; source `eu/src/data/bss/Bss_main_0206076c.c`.

16 BSS bytes used as temporary resource-dictionary name storage.

attach_child_object clears all 16 bytes, copies the supplied initialization string, uses the buffer for NNS_G3dGetResDictIdxByName and stores the resulting index at child+0xc8 before linking the parent/child list.

Limits: The native function uses strcpy and adds no length check. Preserve the 16-byte dictionary-name storage; no wider character encoding, ownership transfer or asynchronous use is established.

Pinned references:

- `eu/src/calls/attach_child_object.c` → `src/arm9/runtime/attach_child_object_0202f500.c`; line(s) 6, 17, 18, 25.
- `eu/src/data/bss/Bss_main_0206076c.c`; line(s) 3.

### `main:02060780` → `gMeshCacheGenerationStorage`

Previous label `data_02060780`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02060780.c`.

4 BSS bytes whose low byte is the mesh-cache generation token.

InitMeshData and SetMeshEnabled increment the low byte when mesh state changes. CachedBounds_NeedsRefresh and RefreshActorMeshCache compare and copy that byte into per-object cache stamps; InitTrackingState also copies it into its record.

Limits: This is an 8-bit wrapping generation, not an elapsed frame counter. Preserve the three remaining bytes and the 4-byte native allocation.

Pinned references:

- `eu/src/calls/CachedBounds_NeedsRefresh.c` → `src/arm9/spatial_queries/CachedBounds_NeedsRefresh_02035044.c`; line(s) 16, 20, 21.
- `eu/src/calls/InitMeshData.c` → `src/arm9/spatial_queries/InitMeshData_020303c4.c`; line(s) 34, 123.
- `eu/src/calls/InitTrackingState.c` → `src/arm9/unclassified_helpers/InitTrackingState_02038a90.c`; line(s) 37, 60.
- `eu/src/calls/RefreshActorMeshCache.c` → `src/arm9/spatial_queries/RefreshActorMeshCache_02038130.c`; line(s) 57, 101, 102.
- `eu/src/data/bss/Bss_main_02060780.c`; line(s) 4.
- `eu/src/overlays/ov001/calls/SetMeshEnabled.c` → `src/ov001/unclassified_helpers/SetMeshEnabled_02068180.c`; line(s) 8, 13, 17.

### `main:02060784` → `gPreservedCollisionHitStorage`

Previous label `data_02060784`; size **184 bytes**; source `eu/src/data/bss/Bss_main_02060780.c`.

184 BSS bytes matching the 46-word CollHitRecord copy used by the preserve-state collision wrapper.

CollWorld_FindHitPreserveState first copies the shared DTCM hit record here, saves traversal frames/top, runs the nested query and restores the previous DTCM record and traversal state. On a hit it then replaces this storage with the query result and returns its address.

Limits: The returned pointer is borrowed shared storage and a later call overwrites it. On a miss the function returns NULL; do not infer an empty result object. This backup does not resolve the distinct overlapping DTCM field layouts.

Pinned references:

- `eu/src/calls/CollWorld_FindHitPreserveState.c` → `src/arm9/spatial_queries/CollWorld_FindHitPreserveState_02034ab4.c`; line(s) 13, 24, 31, 35, 36.
- `eu/src/data/bss/Bss_main_02060780.c`; line(s) 3.

### `main:02060840` → `gSharedModelResourceState`

Previous label `data_02060840`; size **8 bytes**; source `eu/src/data/bss/Bss_main_0206083c.c`.

8 BSS bytes: model pointer followed by the owning model-file pointer.

LoadSharedModel loads the file, dispatches its resources and takes model index 0 from the model set. ShadowVolume_Init uses a pointer to the first word when its explicit model argument is NULL. DeferredDraw_Release releases the file resources, frees the file and clears both words.

Limits: The model is borrowed from the file. This block preserves the existing native ownership and the original explicit-model branch that stores the address of its model parameter; no host lifetime repair is made by renaming DATA.

Pinned references:

- `eu/src/calls/DeferredDraw_Release.c` → `src/arm9/shared_engine/DeferredDraw_Release_02036b20.c`; line(s) 4, 6, 7, 8, 9, 10.
- `eu/src/calls/LoadSharedModel.c` → `src/arm9/graphics/LoadSharedModel_02036ac0.c`; line(s) 9, 40, 42, 44, 45.
- `eu/src/calls/ShadowVolume_Init.c` → `src/arm9/graphics/ShadowVolume_Init_02036b44.c`; line(s) 15, 22.
- `eu/src/data/bss/Bss_main_0206083c.c`; line(s) 3.


## Byte-exact validation

103 DATA identities retain their source paths, native sizes and storage.
405/410 affected official function checks pass; the remaining
5 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 474 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
