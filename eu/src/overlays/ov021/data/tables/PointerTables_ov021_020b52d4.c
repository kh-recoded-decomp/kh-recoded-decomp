#include "nitro/types.h"

extern void ScriptOp_GetPlayerHorizontalOffset(void); /* ScriptOp_GetPlayerHorizontalOffset */
extern void ScriptOp_GetPlayerHorizontalDrift(void); /* ScriptOp_GetPlayerHorizontalDrift */
extern void func_ov021_020b12b8(void);
extern void ScriptOp_GetObjectVectorMagnitude(void); /* ScriptOp_GetObjectVectorMagnitude */
extern void ScriptOp_IsStageEntryKind24(void); /* ScriptOp_IsStageEntryKind24 */
extern void StageScriptExpr_GetSequenceId(void);
extern void ScriptOp_GetPlayerLockFlag(void); /* ScriptOp_GetPlayerLockFlag */
extern void ScriptCmd_GetTargetFacingDot(void); /* ScriptCmd_GetTargetFacingDot */
extern void ScriptOp_GetObjectVerticalOffset(void); /* ScriptOp_GetObjectVerticalOffset */
extern void ScriptOp_IsObjectCounterNonpositive(void); /* ScriptOp_IsObjectCounterNonpositive */
extern void StageScriptExpr_GetVectorX(void);
extern void StageScriptExpr_GetVectorY(void);
extern void StageScriptExpr_GetVectorZ(void);
extern void ReadContextFlagBit8(void); /* ReadContextFlagBit8 */
extern void ScriptOp_GetObjectFixedField(void); /* ScriptOp_GetObjectFixedField */
extern void func_ov021_020b10c0(void);
extern void func_ov021_020b10b0(void);
extern void ReadContextFlagBit9(void); /* ReadContextFlagBit9 */
extern void ScriptOp_GetPlayerStateBit0(void); /* ScriptOp_GetPlayerStateBit0 */
extern void ScriptOp_GetAttachPointScale(void); /* ScriptOp_GetAttachPointScale */
extern void ScriptOp_GetOwnerIntegerField(void); /* ScriptOp_GetOwnerIntegerField */
extern void StageExpr_GetSelectedCommandEntryId(void);
extern void ScriptOp_GetPlayerAngleDegrees(void); /* ScriptOp_GetPlayerAngleDegrees */
extern void ScriptCmd_CheckTargetLineOfSight(void); /* ScriptCmd_CheckTargetLineOfSight */
extern void func_ov021_020b0edc(void);
extern void SampleGridCellValue(void); /* SampleGridCellValue */
extern void ScriptOp_GetObjectTypeId(void); /* ScriptOp_GetObjectTypeId */
extern void func_ov021_020b0e24(void);
extern void func_ov021_020b0df0(void);
extern void func_ov021_020b0dd4(void);
extern void StageExpr_FindFarthestFreeSlotAtOrAboveHeight(void);
extern void ScriptOp_FindNearestFreeSlot(void); /* ScriptOp_FindNearestFreeSlot */
extern void StageExpr_FindNearestFreeSlot(void);
extern void ScriptOp_GetActiveObjectValue(void); /* ScriptOp_GetActiveObjectValue */
extern void ReadContextFlagBit10(void); /* ReadContextFlagBit10 */
extern void ScriptOp_GetFirstSharedValue(void); /* ScriptOp_GetFirstSharedValue */
extern void ScriptOp_GetSecondSharedValue(void); /* ScriptOp_GetSecondSharedValue */
extern void ReadContextFlagBit11(void); /* ReadContextFlagBit11 */
extern void ScriptOp_IsPlayerAnimDone(void); /* ScriptOp_IsPlayerAnimDone */
extern void StageScriptExpr_GetEventEffectKind(void);
extern void ScriptOp_GetEventActorValue(void); /* ScriptOp_GetEventActorValue */
extern void StageScriptExpr_TestSessionFlag3713(void);
extern void ScriptOp_GetEventFlagPairBits(void); /* ScriptOp_GetEventFlagPairBits */
extern void ReadContextFlagBit13(void); /* ReadContextFlagBit13 */
extern void StageScriptExpr_GetHudGauge0BlinkActive(void);
extern void func_ov021_020b0af0(void);
extern void func_ov021_020b0ad4(void);
extern void ScriptOp_GetPlayerHiddenFlag(void); /* ScriptOp_GetPlayerHiddenFlag */
extern void StageExpr_FindFarthestFreeSlot(void);
extern void SetScriptContextVector(void); /* SetScriptContextVector */
extern void AddScriptContextVector(void); /* AddScriptContextVector */
extern void SubmitActorRender(void); /* SubmitActorRender */
extern void StageScriptVec_AddRandomHorizontalOffset(void);
extern void PickSpawnPointNearPlayer(void); /* PickSpawnPointNearPlayer */
extern void ScriptOp_GetObjectPosition(void); /* ScriptOp_GetObjectPosition */
extern void ScriptOp_DropToGround(void); /* ScriptOp_DropToGround */
extern void ScriptOp_MoveAlongPlayerFacing(void); /* ScriptOp_MoveAlongPlayerFacing */
extern void ScriptOp_MoveAgainstPlayerFacing(void); /* ScriptOp_MoveAgainstPlayerFacing */
extern void ScriptOp_StepTowardPlayer(void); /* ScriptOp_StepTowardPlayer */
extern void ScriptOp_GetCameraTarget(void); /* ScriptOp_GetCameraTarget */
extern void StageScriptVec_GetActorNodePosition(void);
extern void ScriptOp_GetObjectPositionById(void); /* ScriptOp_GetObjectPositionById */
extern void ScriptOp_GetStageAnchorB(void); /* ScriptOp_GetStageAnchorB */
extern void ScriptOp_GetStageAnchorA(void); /* ScriptOp_GetStageAnchorA */
extern void LoadSavedPosition(void); /* LoadSavedPosition */
extern void ScriptOp_GetGridCellPosition(void); /* ScriptOp_GetGridCellPosition */
extern void StageCmd_StoreCurrentMotionGridCellCenter(void);
extern void func_ov021_020b1a9c(void);
extern void ScriptOp_GetSlotPosition(void); /* ScriptOp_GetSlotPosition */
extern void ScriptOp_ProjectObjectMovement(void); /* ScriptOp_ProjectObjectMovement */
extern void LoadStageEntryPosition(void); /* LoadStageEntryPosition */
extern void ScriptOp_PlaceAroundPlayer(void); /* ScriptOp_PlaceAroundPlayer */
extern void ScriptOp_PlaceNearPlayerOnGround(void); /* ScriptOp_PlaceNearPlayerOnGround */
extern void ScriptOp_GetMotionTarget(void); /* ScriptOp_GetMotionTarget */
extern void ScriptCmd_PushRandomSpherical(void); /* ScriptCmd_PushRandomSpherical */
extern void ScriptCmd_PushRandomHorizontal(void); /* ScriptCmd_PushRandomHorizontal */
extern void ScriptOp_GetMotionAnchor(void); /* ScriptOp_GetMotionAnchor */
extern void ScriptOp_FindNearbyOpenCell(void); /* ScriptOp_FindNearbyOpenCell */

void (*gScriptQueryHandlers[173])(void) = {
    NULL,
    ScriptOp_GetPlayerHorizontalOffset, /* ScriptOp_GetPlayerHorizontalOffset */
    ScriptOp_GetPlayerHorizontalDrift, /* ScriptOp_GetPlayerHorizontalDrift */
    func_ov021_020b12b8,
    ScriptOp_GetObjectVectorMagnitude, /* ScriptOp_GetObjectVectorMagnitude */
    ScriptOp_IsStageEntryKind24, /* ScriptOp_IsStageEntryKind24 */
    StageScriptExpr_GetSequenceId,
    ScriptOp_GetPlayerLockFlag, /* ScriptOp_GetPlayerLockFlag */
    ScriptCmd_GetTargetFacingDot, /* ScriptCmd_GetTargetFacingDot */
    ScriptOp_GetObjectVerticalOffset, /* ScriptOp_GetObjectVerticalOffset */
    ScriptOp_IsObjectCounterNonpositive, /* ScriptOp_IsObjectCounterNonpositive */
    NULL,
    NULL,
    StageScriptExpr_GetVectorX,
    StageScriptExpr_GetVectorY,
    StageScriptExpr_GetVectorZ,
    NULL,
    ReadContextFlagBit8, /* ReadContextFlagBit8 */
    NULL,
    ScriptOp_GetObjectFixedField, /* ScriptOp_GetObjectFixedField */
    NULL,
    NULL,
    func_ov021_020b10c0,
    func_ov021_020b10b0,
    ReadContextFlagBit9, /* ReadContextFlagBit9 */
    ScriptOp_GetPlayerStateBit0, /* ScriptOp_GetPlayerStateBit0 */
    NULL,
    NULL,
    ScriptOp_GetAttachPointScale, /* ScriptOp_GetAttachPointScale */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetOwnerIntegerField, /* ScriptOp_GetOwnerIntegerField */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    StageExpr_GetSelectedCommandEntryId,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetPlayerAngleDegrees, /* ScriptOp_GetPlayerAngleDegrees */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptCmd_CheckTargetLineOfSight, /* ScriptCmd_CheckTargetLineOfSight */
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0edc,
    SampleGridCellValue, /* SampleGridCellValue */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetObjectTypeId, /* ScriptOp_GetObjectTypeId */
    NULL,
    NULL,
    NULL,
    func_ov021_020b0e24,
    func_ov021_020b0df0,
    NULL,
    func_ov021_020b0dd4,
    NULL,
    StageExpr_FindFarthestFreeSlotAtOrAboveHeight,
    ScriptOp_FindNearestFreeSlot, /* ScriptOp_FindNearestFreeSlot */
    StageExpr_FindNearestFreeSlot,
    NULL,
    NULL,
    ScriptOp_GetActiveObjectValue, /* ScriptOp_GetActiveObjectValue */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ReadContextFlagBit10, /* ReadContextFlagBit10 */
    ScriptOp_GetFirstSharedValue, /* ScriptOp_GetFirstSharedValue */
    ScriptOp_GetSecondSharedValue, /* ScriptOp_GetSecondSharedValue */
    NULL,
    ReadContextFlagBit11, /* ReadContextFlagBit11 */
    ScriptOp_IsPlayerAnimDone, /* ScriptOp_IsPlayerAnimDone */
    NULL,
    NULL,
    NULL,
    NULL,
    StageScriptExpr_GetEventEffectKind,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetEventActorValue, /* ScriptOp_GetEventActorValue */
    NULL,
    StageScriptExpr_TestSessionFlag3713,
    NULL,
    ScriptOp_GetEventFlagPairBits, /* ScriptOp_GetEventFlagPairBits */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ReadContextFlagBit13, /* ReadContextFlagBit13 */
    StageScriptExpr_GetHudGauge0BlinkActive,
    NULL,
    NULL,
    func_ov021_020b0af0,
    func_ov021_020b0ad4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetPlayerHiddenFlag, /* ScriptOp_GetPlayerHiddenFlag */
    StageExpr_FindFarthestFreeSlot,
    NULL,
    NULL,
};

void (*gScriptVectorHandlers[33])(void) = {
    NULL,
    SetScriptContextVector, /* SetScriptContextVector */
    AddScriptContextVector, /* AddScriptContextVector */
    SubmitActorRender, /* SubmitActorRender */
    StageScriptVec_AddRandomHorizontalOffset,
    PickSpawnPointNearPlayer, /* PickSpawnPointNearPlayer */
    ScriptOp_GetObjectPosition, /* ScriptOp_GetObjectPosition */
    ScriptOp_DropToGround, /* ScriptOp_DropToGround */
    ScriptOp_MoveAlongPlayerFacing, /* ScriptOp_MoveAlongPlayerFacing */
    ScriptOp_MoveAgainstPlayerFacing, /* ScriptOp_MoveAgainstPlayerFacing */
    ScriptOp_StepTowardPlayer, /* ScriptOp_StepTowardPlayer */
    ScriptOp_GetCameraTarget, /* ScriptOp_GetCameraTarget */
    StageScriptVec_GetActorNodePosition,
    ScriptOp_GetObjectPositionById, /* ScriptOp_GetObjectPositionById */
    ScriptOp_GetStageAnchorB, /* ScriptOp_GetStageAnchorB */
    ScriptOp_GetStageAnchorA, /* ScriptOp_GetStageAnchorA */
    LoadSavedPosition, /* LoadSavedPosition */
    NULL,
    NULL,
    NULL,
    ScriptOp_GetGridCellPosition, /* ScriptOp_GetGridCellPosition */
    StageCmd_StoreCurrentMotionGridCellCenter,
    func_ov021_020b1a9c,
    ScriptOp_GetSlotPosition, /* ScriptOp_GetSlotPosition */
    ScriptOp_ProjectObjectMovement, /* ScriptOp_ProjectObjectMovement */
    LoadStageEntryPosition, /* LoadStageEntryPosition */
    ScriptOp_PlaceAroundPlayer, /* ScriptOp_PlaceAroundPlayer */
    ScriptOp_PlaceNearPlayerOnGround, /* ScriptOp_PlaceNearPlayerOnGround */
    ScriptOp_GetMotionTarget, /* ScriptOp_GetMotionTarget */
    ScriptCmd_PushRandomSpherical, /* ScriptCmd_PushRandomSpherical */
    ScriptCmd_PushRandomHorizontal, /* ScriptCmd_PushRandomHorizontal */
    ScriptOp_GetMotionAnchor, /* ScriptOp_GetMotionAnchor */
    ScriptOp_FindNearbyOpenCell, /* ScriptOp_FindNearbyOpenCell */
};
