#include "nitro/types.h"

extern BOOL func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern void RequestSceneEvent(u32 index, u32 value, u32 flags);
extern void *data_ov001_020a0528;

BOOL func_ov001_0209c56c(u32 id, u32 value)
{
    s32 sessionMode;

    if (func_ov001_02063a24()) {
        sessionMode = func_ov001_02063a38();
    } else {
        sessionMode = 0;
    }
    if (sessionMode != 6) {
        return FALSE;
    }
    if (data_ov001_020a0528 != NULL) {
        if (id != 0) {
            RequestSceneEvent(id - 1, value, 0);
        }
        return TRUE;
    }
    return FALSE;
}
