#include "nitro/types.h"

extern void ScriptCmd_InitFieldObjectClassTable(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_ActivateFieldObject(void);
extern void ScriptCmd_EnableObjectShadow(void); /* ScriptCmd_EnableObjectShadow */
extern void ScriptCmd_SetFieldObjectClassActivationFlagBit(void);
extern void ScriptCmd_SpawnFieldObjectInSlot(void); /* ScriptCmd_SpawnFieldObjectInSlot */
extern void ScriptCmd_CreateRotatedFieldObject(void); /* ScriptCmd_CreateRotatedFieldObject */
extern void ScriptCmd_SetObjectVisible(void); /* ScriptCmd_SetObjectVisible */
extern void ScriptCmd_SetObjectGroupInteractRange(void); /* ScriptCmd_SetObjectGroupInteractRange */
extern void ScriptCmd_SetObjectAnimation(void); /* ScriptCmd_SetObjectAnimation */
extern void ScriptCmd_RegisterTriggerClass(void); /* ScriptCmd_RegisterTriggerClass */
extern void ScriptCmd_SpawnFieldObject(void); /* ScriptCmd_SpawnFieldObject */
extern void ScriptCmd_CreateWorkSlotObject(void); /* ScriptCmd_CreateWorkSlotObject */
extern void ScriptCmd_CreateRotatedFieldObject_0207ff38(void); /* ScriptCmd_CreateRotatedFieldObject */
extern void ScriptCmd_InitFieldEntryPoolTable(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_SetAuxObjectVisible(void); /* ScriptCmd_SetAuxObjectVisible */
extern void ScriptCmd_ReallocFieldEntryCacheRecord(void);
extern void ScriptOp_SetObjectVector(void); /* ScriptOp_SetObjectVector */
extern void ScriptCmd_CreateTargetViewInSlot(void); /* ScriptCmd_CreateTargetViewInSlot */
extern void ScriptCmd_CreateRunningFieldObject(void); /* ScriptCmd_CreateRunningFieldObject */
extern void ScriptCmd_ConfigureFieldObjectClassLod(void); /* ScriptCmd_SpawnStateSpot */
extern void ScriptCmd_FieldObjectNop14(void); /* DefaultStepDone */
extern void ScriptCmd_FieldObjectNop15(void); /* DefaultStepDone */
extern void ScriptCmd_CreateObjectGroupKindB(void); /* ScriptCmd_CreateObjectGroupKindB */
extern void ScriptCmd_CreateFieldObject(void); /* ScriptCmd_CreateFieldObject */
extern void ScriptCmd_CreateObjectGroupKindD(void); /* ScriptCmd_CreateObjectGroupKindD */
extern void ScriptCmd_CreateFieldObjectWithSaveBits(void); /* ScriptCmd_CreateFieldObjectWithSaveBits */
extern void ScriptCmd_CreateObjectGroupKind7(void); /* ScriptCmd_CreateObjectGroupKind7 */
extern void ScriptCmd_AddGroupObjectAtPosition(void); /* ScriptCmd_AddGroupObjectAtPosition */
extern void ScriptOp_CallObjectVectorHook(void); /* ScriptOp_CallObjectVectorHook */
extern void ScriptCmd_SetObjectHeading(void); /* ScriptCmd_SetObjectHeading */
extern void ScriptCmd_CreateObjectGroupKind9(void); /* ScriptCmd_CreateObjectGroupKind9 */
extern void ScriptCmd_CreateRoamingObject(void); /* ScriptCmd_CreateRoamingObject */
extern void ScriptCmd_CreateGridWidget(void); /* ScriptCmd_CreateGridWidget */
extern void ScriptCmd_CreateFieldObjectFx(void); /* ScriptCmd_CreateFieldObjectFx */
extern void ScriptCmd_RegisterFieldObject(void); /* ScriptCmd_RegisterFieldObject */
extern void ScriptCmd_CreateUpdatingFieldObject(void); /* ScriptCmd_CreateUpdatingFieldObject */
extern void ScriptOp_SetObjectFlag6(void); /* ScriptOp_SetObjectFlag6 */
extern void ScriptCmd_SetObjectCullRadius(void); /* ScriptCmd_SetObjectCullRadius */
extern void ScriptCmd_SetFieldEntryCachePaused(void); /* ScriptCmd_EnterPhase */

void (*gFieldObjectScriptCommandHandlers[78])(void) = {
    ScriptCmd_InitFieldObjectClassTable, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_ActivateFieldObject,
    NULL,
    ScriptCmd_EnableObjectShadow, /* ScriptCmd_EnableObjectShadow */
    NULL,
    ScriptCmd_SetFieldObjectClassActivationFlagBit,
    NULL,
    ScriptCmd_SpawnFieldObjectInSlot, /* ScriptCmd_SpawnFieldObjectInSlot */
    NULL,
    ScriptCmd_CreateRotatedFieldObject, /* ScriptCmd_CreateRotatedFieldObject */
    NULL,
    ScriptCmd_SetObjectVisible, /* ScriptCmd_SetObjectVisible */
    NULL,
    ScriptCmd_SetObjectGroupInteractRange, /* ScriptCmd_SetObjectGroupInteractRange */
    NULL,
    ScriptCmd_SetObjectAnimation, /* ScriptCmd_SetObjectAnimation */
    NULL,
    ScriptCmd_RegisterTriggerClass, /* ScriptCmd_RegisterTriggerClass */
    NULL,
    ScriptCmd_SpawnFieldObject, /* ScriptCmd_SpawnFieldObject */
    NULL,
    ScriptCmd_CreateWorkSlotObject, /* ScriptCmd_CreateWorkSlotObject */
    NULL,
    ScriptCmd_CreateRotatedFieldObject_0207ff38, /* ScriptCmd_CreateRotatedFieldObject */
    NULL,
    ScriptCmd_InitFieldEntryPoolTable, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_SetAuxObjectVisible, /* ScriptCmd_SetAuxObjectVisible */
    NULL,
    ScriptCmd_ReallocFieldEntryCacheRecord,
    NULL,
    ScriptOp_SetObjectVector, /* ScriptOp_SetObjectVector */
    NULL,
    ScriptCmd_CreateTargetViewInSlot, /* ScriptCmd_CreateTargetViewInSlot */
    NULL,
    ScriptCmd_CreateRunningFieldObject, /* ScriptCmd_CreateRunningFieldObject */
    NULL,
    ScriptCmd_ConfigureFieldObjectClassLod, /* ScriptCmd_SpawnStateSpot */
    NULL,
    ScriptCmd_FieldObjectNop14, /* DefaultStepDone */
    NULL,
    ScriptCmd_FieldObjectNop15, /* DefaultStepDone */
    NULL,
    ScriptCmd_CreateObjectGroupKindB, /* ScriptCmd_CreateObjectGroupKindB */
    NULL,
    ScriptCmd_CreateFieldObject, /* ScriptCmd_CreateFieldObject */
    NULL,
    ScriptCmd_CreateObjectGroupKindD, /* ScriptCmd_CreateObjectGroupKindD */
    NULL,
    ScriptCmd_CreateFieldObjectWithSaveBits, /* ScriptCmd_CreateFieldObjectWithSaveBits */
    NULL,
    ScriptCmd_CreateObjectGroupKind7, /* ScriptCmd_CreateObjectGroupKind7 */
    NULL,
    ScriptCmd_AddGroupObjectAtPosition, /* ScriptCmd_AddGroupObjectAtPosition */
    NULL,
    ScriptOp_CallObjectVectorHook, /* ScriptOp_CallObjectVectorHook */
    NULL,
    ScriptCmd_SetObjectHeading, /* ScriptCmd_SetObjectHeading */
    NULL,
    ScriptCmd_CreateObjectGroupKind9, /* ScriptCmd_CreateObjectGroupKind9 */
    NULL,
    ScriptCmd_CreateRoamingObject, /* ScriptCmd_CreateRoamingObject */
    NULL,
    ScriptCmd_CreateGridWidget, /* ScriptCmd_CreateGridWidget */
    NULL,
    ScriptCmd_CreateFieldObjectFx, /* ScriptCmd_CreateFieldObjectFx */
    NULL,
    ScriptCmd_RegisterFieldObject, /* ScriptCmd_RegisterFieldObject */
    NULL,
    ScriptCmd_CreateUpdatingFieldObject, /* ScriptCmd_CreateUpdatingFieldObject */
    NULL,
    ScriptOp_SetObjectFlag6, /* ScriptOp_SetObjectFlag6 */
    NULL,
    ScriptCmd_SetObjectCullRadius, /* ScriptCmd_SetObjectCullRadius */
    NULL,
    ScriptCmd_SetFieldEntryCachePaused, /* ScriptCmd_EnterPhase */
    NULL,
};
