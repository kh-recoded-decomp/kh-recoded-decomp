#include "nitro/types.h"

extern void AddScriptContextVector_020b1f90(void);
extern void LoadSavedPosition_020b1b54(void);
extern void LoadStageEntryPosition_020b19b0(void);
extern void PickSpawnPointNearPlayer_020b1e04(void);
extern void ReadContextFlagBit10_020b0c98(void);
extern void ReadContextFlagBit11_020b0c40(void);
extern void ReadContextFlagBit13_020b0b00(void);
extern void ReadContextFlagBit8_020b10dc(void);
extern void ReadContextFlagBit9_020b1070(void);
extern void SampleGridCellValue_020b0e60(void);
extern void ScriptCmd_CheckTargetLineOfSight_020b0eec(void);
extern void ScriptCmd_GetTargetFacingDot_020b1174(void);
extern void ScriptCmd_PushRandomHorizontal_020b15e8(void);
extern void ScriptCmd_PushRandomSpherical_020b1668(void);
extern void ScriptOp_DropToGround_020b1d78(void);
extern void ScriptOp_FindNearbyOpenCell_020b1374(void);
extern void ScriptOp_FindNearestFreeSlot_020b0d24(void);
extern void ScriptOp_GetActiveObjectValue_020b0cb8(void);
extern void ScriptOp_GetAttachPointScale_020b0ff4(void);
extern void ScriptOp_GetCameraTarget_020b1c30(void);
extern void ScriptOp_GetEventActorValue_020b0b6c(void);
extern void ScriptOp_GetEventFlagPairBits_020b0b20(void);
extern void ScriptOp_GetFirstSharedValue_020b0c7c(void);
extern void ScriptOp_GetGridCellPosition_020b1afc(void);
extern void ScriptOp_GetMotionAnchor_020b15c0(void);
extern void ScriptOp_GetMotionTarget_020b16ec(void);
extern void ScriptOp_GetObjectFixedField_020b10bc(void);
extern void ScriptOp_GetObjectPositionById_020b1bb4(void);
extern void ScriptOp_GetObjectPosition_020b1de4(void);
extern void ScriptOp_GetObjectTypeId_020b0e20(void);
extern void ScriptOp_GetObjectVectorMagnitude_020b1270(void);
extern void ScriptOp_GetObjectVerticalOffset_020b114c(void);
extern void ScriptOp_GetOwnerIntegerField_020b0fd0(void);
extern void ScriptOp_GetPlayerAngleDegrees_020b0f74(void);
extern void ScriptOp_GetPlayerHiddenFlag_020b0a90(void);
extern void ScriptOp_GetPlayerHorizontalDrift_020b12b8(void);
extern void ScriptOp_GetPlayerHorizontalOffset_020b131c(void);
extern void ScriptOp_GetPlayerLockFlag_020b120c(void);
extern void ScriptOp_GetPlayerStateBit0_020b1044(void);
extern void ScriptOp_GetSecondSharedValue_020b0c60(void);
extern void ScriptOp_GetSlotPosition_020b1a30(void);
extern void ScriptOp_GetStageAnchorA_020b1b74(void);
extern void ScriptOp_GetStageAnchorB_020b1b94(void);
extern void ScriptOp_IsObjectCounterNonpositive_020b1120(void);
extern void ScriptOp_IsPlayerAnimDone_020b0be8(void);
extern void ScriptOp_IsStageEntryKind24_020b1240(void);
extern void ScriptOp_MoveAgainstPlayerFacing_020b1cac(void);
extern void ScriptOp_MoveAlongPlayerFacing_020b1d14(void);
extern void ScriptOp_PlaceAroundPlayer_020b1850(void);
extern void ScriptOp_PlaceNearPlayerOnGround_020b1714(void);
extern void ScriptOp_ProjectObjectMovement_020b19d0(void);
extern void ScriptOp_StepTowardPlayer_020b1c50(void);
extern void SetScriptContextVector_020b1fe0(void);
extern void SubmitActorRender_020b1f78(void);
extern void func_ov021_020b0a48(void);
extern void func_ov021_020b0ab4(void);
extern void func_ov021_020b0ad0(void);
extern void func_ov021_020b0aec(void);
extern void func_ov021_020b0b54(void);
extern void func_ov021_020b0bcc(void);
extern void func_ov021_020b0cdc(void);
extern void func_ov021_020b0d6c(void);
extern void func_ov021_020b0db4(void);
extern void func_ov021_020b0dd0(void);
extern void func_ov021_020b0e04(void);
extern void func_ov021_020b0ebc(void);
extern void func_ov021_020b0fb4(void);
extern void func_ov021_020b1090(void);
extern void func_ov021_020b10a0(void);
extern void func_ov021_020b10fc(void);
extern void func_ov021_020b1108(void);
extern void func_ov021_020b1114(void);
extern void func_ov021_020b1230(void);
extern void func_ov021_020b1298(void);
extern void func_ov021_020b1a7c(void);
extern void func_ov021_020b1ad4(void);
extern void func_ov021_020b1be4(void);
extern void func_ov021_020b1f34(void);

void (*data_ov021_020b5338[173])(void) = {
    NULL,
    ScriptOp_GetPlayerHorizontalOffset_020b131c,
    ScriptOp_GetPlayerHorizontalDrift_020b12b8,
    func_ov021_020b1298,
    ScriptOp_GetObjectVectorMagnitude_020b1270,
    ScriptOp_IsStageEntryKind24_020b1240,
    func_ov021_020b1230,
    ScriptOp_GetPlayerLockFlag_020b120c,
    ScriptCmd_GetTargetFacingDot_020b1174,
    ScriptOp_GetObjectVerticalOffset_020b114c,
    ScriptOp_IsObjectCounterNonpositive_020b1120,
    NULL,
    NULL,
    func_ov021_020b1114,
    func_ov021_020b1108,
    func_ov021_020b10fc,
    NULL,
    ReadContextFlagBit8_020b10dc,
    NULL,
    ScriptOp_GetObjectFixedField_020b10bc,
    NULL,
    NULL,
    func_ov021_020b10a0,
    func_ov021_020b1090,
    ReadContextFlagBit9_020b1070,
    ScriptOp_GetPlayerStateBit0_020b1044,
    NULL,
    NULL,
    ScriptOp_GetAttachPointScale_020b0ff4,
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
    ScriptOp_GetOwnerIntegerField_020b0fd0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0fb4,
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
    ScriptOp_GetPlayerAngleDegrees_020b0f74,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptCmd_CheckTargetLineOfSight_020b0eec,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0ebc,
    SampleGridCellValue_020b0e60,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetObjectTypeId_020b0e20,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0e04,
    func_ov021_020b0dd0,
    NULL,
    func_ov021_020b0db4,
    NULL,
    func_ov021_020b0d6c,
    ScriptOp_FindNearestFreeSlot_020b0d24,
    func_ov021_020b0cdc,
    NULL,
    NULL,
    ScriptOp_GetActiveObjectValue_020b0cb8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ReadContextFlagBit10_020b0c98,
    ScriptOp_GetFirstSharedValue_020b0c7c,
    ScriptOp_GetSecondSharedValue_020b0c60,
    NULL,
    ReadContextFlagBit11_020b0c40,
    ScriptOp_IsPlayerAnimDone_020b0be8,
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov021_020b0bcc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetEventActorValue_020b0b6c,
    NULL,
    func_ov021_020b0b54,
    NULL,
    ScriptOp_GetEventFlagPairBits_020b0b20,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ReadContextFlagBit13_020b0b00,
    func_ov021_020b0aec,
    NULL,
    NULL,
    func_ov021_020b0ad0,
    func_ov021_020b0ab4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetPlayerHiddenFlag_020b0a90,
    func_ov021_020b0a48,
    NULL,
    NULL,
};

void (*data_ov021_020b52b4[33])(void) = {
    NULL,
    SetScriptContextVector_020b1fe0,
    AddScriptContextVector_020b1f90,
    SubmitActorRender_020b1f78,
    func_ov021_020b1f34,
    PickSpawnPointNearPlayer_020b1e04,
    ScriptOp_GetObjectPosition_020b1de4,
    ScriptOp_DropToGround_020b1d78,
    ScriptOp_MoveAlongPlayerFacing_020b1d14,
    ScriptOp_MoveAgainstPlayerFacing_020b1cac,
    ScriptOp_StepTowardPlayer_020b1c50,
    ScriptOp_GetCameraTarget_020b1c30,
    func_ov021_020b1be4,
    ScriptOp_GetObjectPositionById_020b1bb4,
    ScriptOp_GetStageAnchorB_020b1b94,
    ScriptOp_GetStageAnchorA_020b1b74,
    LoadSavedPosition_020b1b54,
    NULL,
    NULL,
    NULL,
    ScriptOp_GetGridCellPosition_020b1afc,
    func_ov021_020b1ad4,
    func_ov021_020b1a7c,
    ScriptOp_GetSlotPosition_020b1a30,
    ScriptOp_ProjectObjectMovement_020b19d0,
    LoadStageEntryPosition_020b19b0,
    ScriptOp_PlaceAroundPlayer_020b1850,
    ScriptOp_PlaceNearPlayerOnGround_020b1714,
    ScriptOp_GetMotionTarget_020b16ec,
    ScriptCmd_PushRandomSpherical_020b1668,
    ScriptCmd_PushRandomHorizontal_020b15e8,
    ScriptOp_GetMotionAnchor_020b15c0,
    ScriptOp_FindNearbyOpenCell_020b1374,
};
