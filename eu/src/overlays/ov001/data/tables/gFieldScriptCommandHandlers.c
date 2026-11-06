#include "nitro/types.h"

extern void ScriptCmd_FieldNoop0(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_RequestRoomChange(void); /* ScriptCmd_RequestRoomChange */
extern void ScriptCmd_SwitchFieldMode(void); /* ScriptCmd_SwitchFieldMode */
extern void ScriptCmd_FieldNoop3(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_EnterMenuItem(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_LoadFieldObjectSet(void); /* ScriptCmd_LoadFieldObjectSet */
extern void ScriptOp_StartFieldMotion(void); /* ScriptOp_StartFieldMotion */
extern void ScriptCmd_QueueFlagTaskKind1(void); /* ScriptCmd_QueueFlagTaskKind1 */
extern void ScriptCmd_QueueFlagTaskKind2(void);
extern void ScriptOp_StartFieldTimerAt(void); /* ScriptOp_StartFieldTimerAt */
extern void ScriptOp_StartFieldTimer(void); /* ScriptOp_StartFieldTimer */
extern void ScriptCmd_StartSessionScene(void); /* return 0; ByteCode_ResolveOperand */
extern void ScriptCmd_UnpauseFieldEntriesIfFlag20Clear(void);
extern void ScriptCmd_LoadLevelTableFile(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_QueueEventPair(void); /* ScriptCmd_QueueEventPair */
extern void ScriptCmd_SetMapGimmickState(void); /* ScriptCmd_SetMapGimmickState */
extern void ScriptCmd_PlayMapLayerAnimation(void); /* ScriptCmd_PlayMapLayerAnimation */
extern void ScriptCmd_SetSpawnPoint(void); /* ScriptCmd_SetSpawnPoint */
extern void ScriptCmd_LoadSceneTable(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SetMapGimmickFlags(void); /* ScriptCmd_SetMapGimmickFlags */
extern void ScriptCmd_SetNamedMapNodesVisible(void); /* ScriptCmd_SetNamedMapNodesVisible */
extern void ScriptCmd_ReleaseOrDisableStageEvent(void);
extern void ScriptCmd_QueueFlagTaskKind3(void); /* ScriptCmd_QueueFlagTaskKind3 */
extern void ScriptCmd_ShowSessionNameEntry(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_EnsureFieldEffectPool(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_LoadOffsetTableFile(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_CommitChapterClearRecords(void); /* return 1; no local decode */
extern void ScriptCmd_SetFieldCameraModeRequest(void); /* ScriptCmd_SetWorldByte8D68 */
extern void ScriptCmd_QueueFlagTaskKind4(void); /* ScriptCmd_QueueFlagTaskKind4 */
extern void ScriptCmd_AdjustItemCount(void); /* ScriptCmd_AdjustItemCount */
extern void ScriptCmd_SetSessionFlag35e3(void);
extern void ScriptCmd_SetFieldParameter(void); /* ScriptCmd_SetFieldParameter */
extern void ScriptCmd_RestorePrimaryActorHealth(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_SetMenuItemKind(void);
extern void ScriptCmd_SetSceneSlotDrawingEnabled(void);
extern void ScriptOp_SetVector4(void); /* ScriptOp_SetVector4 */
extern void ScriptCmd_RequestSubScene9(void); /* ScriptCmd_RequestSubScene9 */
extern void ScriptCmd_WaitForSubScene9RequestReady(void); /* IsSceneState0 */
extern void ScriptCmd_ResetStageGroupRowsAndRestoreDefault(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_HandleFieldPanelCommand(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SetPartyEntryUpdatesEnabled(void); /* ScriptCmd_SetPartyEntryUpdatesEnabled */
extern void ScriptCmd_PlayFieldBgm(void); /* ScriptCmd_PlayFieldBgm */
extern void ScriptCmd_LoadCameraParams(void); /* return 1; ByteCode_ResolveOperand */
extern void ScriptCmd_SetIndexedSaveFlag(void); /* ScriptCmd_SetIndexedSaveFlag */
extern void ScriptCmd_OpenFieldMenuMode(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SetSceneLock(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_LoadSceneData(void);
extern void ScriptCmd_ClearSceneEntry(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_WaitForState4CameraOffsetToClear(void);
extern void ScriptCmd_ShowHudIndicator(void); /* ScriptCmd_ShowHudIndicator */
extern void ScriptCmd_WaitForCounterHudFadeState0(void); /* IsSceneState0 */
extern void ScriptCmd_ResetStageOriginIfActive(void); /* return 1; no local decode */
extern void ScriptCmd_StartCameraShake(void); /* ScriptCmd_StartCameraShake */
extern void ScriptCmd_SetCameraHorizontalFollowBounds(void);
extern void ScriptCmd_QueueFlagTaskKind6(void); /* ScriptCmd_QueueFlagTaskKind6 */
extern void ScriptOp_SendPayloadWords(void); /* ScriptOp_SendPayloadWords */
extern void ScriptCmd_ResetOverlaySelection(void); /* return 1; no local decode */
extern void ScriptOp_AddSessionBits(void); /* ScriptOp_AddSessionBits */
extern void ScriptCmd_LoadCenteredScreenSprite(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_RequestAreaChange(void); /* ScriptCmd_RequestAreaChange */
extern void ScriptCmd_AdvanceRecordStep(void); /* return 1; no local decode */
extern void ScriptCmd_SetSceneScrollSpeedTarget(void);
extern void ScriptCmd_SetAngleDegrees(void); /* ScriptCmd_SetAngleDegrees */
extern void ScriptCmd_AddStageSlotLock1(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_TryActivateStageSlot(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SetFieldObjectsFlag(void); /* ScriptCmd_SetFieldObjectsFlag */
extern void ScriptCmd_SetOv043CameraFlags8(void);
extern void ScriptCmd_EnterPanelModeThree(void); /* CmdOpenDialog */
extern void ScriptCmd_TestSceneFlag10Clear(void); /* thumbStep */
extern void ScriptCmd_FieldOp41RunZero(void); /* FSi_CloseFileCommand */
extern void ScriptCmd_SaveCurrentSpawnPoint(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SaveCheckpoint(void);
extern void ScriptCmd_SetMenuHighlight(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_ForwardSubModeStart(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_BeginCommonFieldMessageSpriteWait(void);
extern void ScriptCmd_AdvanceCommonFieldMessageSpriteWait(void);
extern void ScriptCmd_ConfigureEventSlot(void); /* ScriptCmd_ConfigureEventSlot */
extern void ScriptCmd_SpawnRewardAtActor(void); /* ScriptCmd_SpawnRewardAtActor */
extern void ScriptCmd_WaitForFieldEffectsThenSuspend(void);
extern void ScriptCmd_PlacePartyMember(void);
extern void ScriptCmd_BindScriptHandlersSlot7(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_StoreRandomBits(void); /* ScriptCmd_StoreRandomBits */
extern void ScriptCmd_AllocSessionNameTable(void); /* return 1; ScriptVm_ReadOperandInt */
extern void ScriptCmd_SetSessionTableName(void); /* ScriptCmd_SetLinkMode */
extern void ScriptCmd_QueueFlagTaskKind8(void); /* ScriptCmd_QueueFlagTaskKind8 */
extern void ScriptCmd_QueueStage900AndSavePlacement(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_StorePageVariantParams(void); /* ScriptCmd_StorePageVariantParams */
extern void ScriptCmd_StoreFifoReady(void);
extern void ScriptCmd_QueueFieldFromSavedSceneIds(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_RefreshFirstSelectionPlayerStats(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_SetupSlotPanelMode(void);
extern void ScriptCmd_ToggleSessionBit15(void); /* ScriptCmd_ToggleSessionBit15 */
extern void ScriptCmd_RequestFieldExitToScene4(void);
extern void ScriptCmd_DamageLeaderNonLethal(void);
extern void ScriptCmd_SetSessionByte27B6Bit5(void);
extern void ScriptCmd_ClearSessionStateWords(void); /* return 1; no local decode */
extern void ScriptCmd_InvokeSessionCallback(void); /* MsgQueue_GetHeap */
extern void ScriptCmd_TestSessionCheckCallback(void); /* thumbStep */
extern void ScriptCmd_AwardSlotLevelProgress(void);
extern void ScriptCmd_SetSceneEntryValueOverride(void); /* scene-entry value override */
extern void ScriptCmd_ResetGaugeDisplay(void); /* return 1; no local decode */
extern void ScriptCmd_RestoreSelectionRecordValue(void); /* ScriptCmd_RestoreSelectionRecordValue */

void (*gFieldScriptCommandHandlers[190])(void) = {
    ScriptCmd_FieldNoop0, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_RequestRoomChange, /* ScriptCmd_RequestRoomChange */
    NULL,
    ScriptCmd_SwitchFieldMode, /* ScriptCmd_SwitchFieldMode */
    NULL,
    ScriptCmd_FieldNoop3, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_EnterMenuItem, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_LoadFieldObjectSet, /* ScriptCmd_LoadFieldObjectSet */
    NULL,
    ScriptOp_StartFieldMotion, /* ScriptOp_StartFieldMotion */
    NULL,
    ScriptCmd_QueueFlagTaskKind1, /* ScriptCmd_QueueFlagTaskKind1 */
    NULL,
    ScriptCmd_QueueFlagTaskKind2,
    NULL,
    ScriptOp_StartFieldTimerAt, /* ScriptOp_StartFieldTimerAt */
    NULL,
    ScriptOp_StartFieldTimer, /* ScriptOp_StartFieldTimer */
    NULL,
    ScriptCmd_StartSessionScene, /* return 0; ByteCode_ResolveOperand */
    ScriptCmd_UnpauseFieldEntriesIfFlag20Clear,
    ScriptCmd_LoadLevelTableFile, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_QueueEventPair, /* ScriptCmd_QueueEventPair */
    NULL,
    ScriptCmd_SetMapGimmickState, /* ScriptCmd_SetMapGimmickState */
    NULL,
    ScriptCmd_PlayMapLayerAnimation, /* ScriptCmd_PlayMapLayerAnimation */
    NULL,
    ScriptCmd_SetSpawnPoint, /* ScriptCmd_SetSpawnPoint */
    NULL,
    ScriptCmd_LoadSceneTable, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SetMapGimmickFlags, /* ScriptCmd_SetMapGimmickFlags */
    NULL,
    ScriptCmd_SetNamedMapNodesVisible, /* ScriptCmd_SetNamedMapNodesVisible */
    NULL,
    ScriptCmd_ReleaseOrDisableStageEvent,
    NULL,
    ScriptCmd_QueueFlagTaskKind3, /* ScriptCmd_QueueFlagTaskKind3 */
    NULL,
    ScriptCmd_ShowSessionNameEntry, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_EnsureFieldEffectPool, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_LoadOffsetTableFile, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_CommitChapterClearRecords, /* return 1; no local decode */
    NULL,
    ScriptCmd_SetFieldCameraModeRequest, /* ScriptCmd_SetWorldByte8D68 */
    NULL,
    ScriptCmd_QueueFlagTaskKind4, /* ScriptCmd_QueueFlagTaskKind4 */
    NULL,
    ScriptCmd_AdjustItemCount, /* ScriptCmd_AdjustItemCount */
    NULL,
    ScriptCmd_SetSessionFlag35e3,
    NULL,
    ScriptCmd_SetFieldParameter, /* ScriptCmd_SetFieldParameter */
    NULL,
    ScriptCmd_RestorePrimaryActorHealth, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_SetMenuItemKind,
    NULL,
    ScriptCmd_SetSceneSlotDrawingEnabled,
    NULL,
    ScriptOp_SetVector4, /* ScriptOp_SetVector4 */
    NULL,
    ScriptCmd_RequestSubScene9, /* ScriptCmd_RequestSubScene9 */
    ScriptCmd_WaitForSubScene9RequestReady, /* IsSceneState0 */
    ScriptCmd_ResetStageGroupRowsAndRestoreDefault, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_HandleFieldPanelCommand, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SetPartyEntryUpdatesEnabled, /* ScriptCmd_SetPartyEntryUpdatesEnabled */
    NULL,
    ScriptCmd_PlayFieldBgm, /* ScriptCmd_PlayFieldBgm */
    NULL,
    ScriptCmd_LoadCameraParams, /* return 1; ByteCode_ResolveOperand */
    NULL,
    ScriptCmd_SetIndexedSaveFlag, /* ScriptCmd_SetIndexedSaveFlag */
    NULL,
    ScriptCmd_OpenFieldMenuMode, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SetSceneLock, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_LoadSceneData,
    NULL,
    ScriptCmd_ClearSceneEntry, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_WaitForState4CameraOffsetToClear,
    ScriptCmd_WaitForState4CameraOffsetToClear,
    ScriptCmd_ShowHudIndicator, /* ScriptCmd_ShowHudIndicator */
    ScriptCmd_WaitForCounterHudFadeState0, /* IsSceneState0 */
    ScriptCmd_ResetStageOriginIfActive, /* return 1; no local decode */
    NULL,
    ScriptCmd_StartCameraShake, /* ScriptCmd_StartCameraShake */
    NULL,
    ScriptCmd_SetCameraHorizontalFollowBounds,
    NULL,
    ScriptCmd_QueueFlagTaskKind6, /* ScriptCmd_QueueFlagTaskKind6 */
    NULL,
    ScriptOp_SendPayloadWords, /* ScriptOp_SendPayloadWords */
    NULL,
    ScriptCmd_ResetOverlaySelection, /* return 1; no local decode */
    NULL,
    ScriptOp_AddSessionBits, /* ScriptOp_AddSessionBits */
    NULL,
    ScriptCmd_LoadCenteredScreenSprite, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_RequestAreaChange, /* ScriptCmd_RequestAreaChange */
    NULL,
    ScriptCmd_AdvanceRecordStep, /* return 1; no local decode */
    NULL,
    ScriptCmd_SetSceneScrollSpeedTarget,
    NULL,
    ScriptCmd_SetAngleDegrees, /* ScriptCmd_SetAngleDegrees */
    NULL,
    ScriptCmd_AddStageSlotLock1, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_TryActivateStageSlot, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SetFieldObjectsFlag, /* ScriptCmd_SetFieldObjectsFlag */
    NULL,
    ScriptCmd_SetOv043CameraFlags8,
    NULL,
    ScriptCmd_EnterPanelModeThree, /* CmdOpenDialog */
    ScriptCmd_TestSceneFlag10Clear, /* thumbStep */
    ScriptCmd_FieldOp41RunZero, /* FSi_CloseFileCommand */
    NULL,
    ScriptCmd_SaveCurrentSpawnPoint, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SaveCheckpoint,
    NULL,
    ScriptCmd_SetMenuHighlight, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_ForwardSubModeStart, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_BeginCommonFieldMessageSpriteWait,
    ScriptCmd_AdvanceCommonFieldMessageSpriteWait,
    ScriptCmd_ConfigureEventSlot, /* ScriptCmd_ConfigureEventSlot */
    NULL,
    ScriptCmd_SpawnRewardAtActor, /* ScriptCmd_SpawnRewardAtActor */
    ScriptCmd_WaitForFieldEffectsThenSuspend,
    ScriptCmd_PlacePartyMember,
    NULL,
    ScriptCmd_BindScriptHandlersSlot7, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_StoreRandomBits, /* ScriptCmd_StoreRandomBits */
    NULL,
    ScriptCmd_AllocSessionNameTable, /* return 1; ScriptVm_ReadOperandInt */
    NULL,
    ScriptCmd_SetSessionTableName, /* ScriptCmd_SetLinkMode */
    NULL,
    ScriptCmd_QueueFlagTaskKind8, /* ScriptCmd_QueueFlagTaskKind8 */
    NULL,
    ScriptCmd_QueueStage900AndSavePlacement, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_StorePageVariantParams, /* ScriptCmd_StorePageVariantParams */
    NULL,
    ScriptCmd_StoreFifoReady,
    NULL,
    ScriptCmd_QueueFieldFromSavedSceneIds, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_RefreshFirstSelectionPlayerStats, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_SetupSlotPanelMode,
    NULL,
    ScriptCmd_ToggleSessionBit15, /* ScriptCmd_ToggleSessionBit15 */
    NULL,
    ScriptCmd_RequestFieldExitToScene4,
    NULL,
    ScriptCmd_DamageLeaderNonLethal,
    NULL,
    ScriptCmd_SetSessionByte27B6Bit5,
    NULL,
    ScriptCmd_ClearSessionStateWords, /* return 1; no local decode */
    NULL,
    ScriptCmd_InvokeSessionCallback, /* MsgQueue_GetHeap */
    ScriptCmd_TestSessionCheckCallback, /* thumbStep */
    ScriptCmd_AwardSlotLevelProgress,
    NULL,
    ScriptCmd_SetSceneEntryValueOverride, /* scene-entry value override */
    NULL,
    ScriptCmd_ResetGaugeDisplay, /* return 1; no local decode */
    NULL,
    ScriptCmd_RestoreSelectionRecordValue, /* ScriptCmd_RestoreSelectionRecordValue */
    NULL,
};
