#include "nitro/types.h"

extern BOOL Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern void func_ov035_020bae84(u32 index, u32 value, u32 flags);
extern void *g_stageManager_020a0508;

BOOL func_ov001_0209c544(u32 id, u32 value)
{
    s32 sessionMode;

    if (Session_Exists_02063a24()) {
        sessionMode = func_ov001_02063a38();
    } else {
        sessionMode = 0;
    }
    if (sessionMode != 6) {
        return FALSE;
    }
    if (g_stageManager_020a0508 != NULL) {
        if (id != 0) {
            func_ov035_020bae84(id - 1, value, 0);
        }
        return TRUE;
    }
    return FALSE;
}
