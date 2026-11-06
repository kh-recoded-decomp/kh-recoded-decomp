#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ScriptCmd_ApplyEntityColorParams(void);
extern void ScriptCmd_ApplyEntityColorVecParams(void);
extern void ScriptCmd_ApplyEntryValues(void);
extern void ScriptCmd_ApplyPackedIds(void);
extern void ScriptCmd_LoadOverlayKind9(void);
extern void ScriptCmd_SetGroupFlag21(void);
extern void ScriptCmd_StoreFieldUnitRecord(void);
extern void ScriptCmd_SpawnFieldObjectTree(void);
extern void ScriptCmd_SpawnFieldObjectTreeWithExtraVector(void);
extern void ScriptCmd_SetFieldObjectFlag22(void);
extern void ScriptCmd_FreeFieldResourceCache(void);

void *gOverlay016ScriptCommandHandlers[26] = {
    (void *)ScriptCmd_LoadOverlayKind9,
    NULL,
    (void *)ScriptCmd_SpawnFieldObjectTree,
    NULL,
    (void *)ScriptCmd_ApplyEntityColorParams,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ScriptCmd_ApplyPackedIds,
    NULL,
    (void *)ScriptCmd_ApplyEntryValues,
    NULL,
    (void *)ScriptCmd_StoreFieldUnitRecord,
    NULL,
    (void *)ScriptCmd_SetGroupFlag21,
    NULL,
    (void *)ScriptCmd_SpawnFieldObjectTreeWithExtraVector,
    NULL,
    (void *)ScriptCmd_ApplyEntityColorVecParams,
    NULL,
    (void *)ScriptCmd_FreeFieldResourceCache,
    NULL,
    (void *)ScriptCmd_SetFieldObjectFlag22,
    NULL,
};
