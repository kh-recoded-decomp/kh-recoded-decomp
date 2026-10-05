#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FS_UnloadOverlayImage_020a2264(void);
extern void ScriptCmd_ApplyEntityColorParams_020a2024(void);
extern void ScriptCmd_ApplyEntityColorVecParams_020a20c0(void);
extern void ScriptCmd_ApplyEntryValues_020a2178(void);
extern void ScriptCmd_ApplyPackedIds_020a2108(void);
extern void ScriptCmd_LoadOverlayKind9_020a1e08(void);
extern void ScriptCmd_SetGroupFlag21_020a21e8(void);
extern void ScriptCmd_StoreFieldUnitRecord_020bfd84(void);
extern void func_ov016_020a2000(void);
extern void func_ov016_020a208c(void);
extern void func_ov016_020a2224(void);

void *data_ov016_020a6e40[26] = {
    (void *)ScriptCmd_LoadOverlayKind9_020a1e08,
    NULL,
    (void *)func_ov016_020a2000,
    NULL,
    (void *)ScriptCmd_ApplyEntityColorParams_020a2024,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ScriptCmd_ApplyPackedIds_020a2108,
    NULL,
    (void *)ScriptCmd_ApplyEntryValues_020a2178,
    NULL,
    (void *)ScriptCmd_StoreFieldUnitRecord_020bfd84,
    NULL,
    (void *)ScriptCmd_SetGroupFlag21_020a21e8,
    NULL,
    (void *)func_ov016_020a208c,
    NULL,
    (void *)ScriptCmd_ApplyEntityColorVecParams_020a20c0,
    NULL,
    (void *)FS_UnloadOverlayImage_020a2264,
    NULL,
    (void *)func_ov016_020a2224,
    NULL,
};
