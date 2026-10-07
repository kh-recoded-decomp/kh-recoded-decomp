#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ScriptCmd_ApplyEntityColorParams(void);
extern void ScriptCmd_ApplyEntityColorVecParams(void);
extern void ScriptCmd_ApplyEntryValues(void);
extern void ScriptCmd_ApplyPackedIds(void);
extern void ScriptCmd_LoadOverlayKind9(void);
extern void ScriptCmd_SetGroupFlag21(void);
extern void ScriptCmd_StoreFieldUnitRecord(void);
extern void func_ov016_020a2020(void);
extern void func_ov016_020a20ac(void);
extern void func_ov016_020a2244(void);
extern void func_ov016_020a2284(void);

void *data_ov016_020a6e60[26] = {
    (void *)ScriptCmd_LoadOverlayKind9,
    NULL,
    (void *)func_ov016_020a2020,
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
    (void *)func_ov016_020a20ac,
    NULL,
    (void *)ScriptCmd_ApplyEntityColorVecParams,
    NULL,
    (void *)func_ov016_020a2284,
    NULL,
    (void *)func_ov016_020a2244,
    NULL,
};
