#include "nitro/types.h"

extern signed char GetCtxModeByte_02068084(void);
extern s32 func_ov007_020a0884(u32 unused, void *obj);

void func_ov001_0206700c(int stateId, u32 *outCleared, void *outHandler)
{
    void *handler = NULL;

    if ((GetCtxModeByte_02068084() == 3) && ((u32)(stateId - 0x1f) <= 1)) {
        handler = (void *)func_ov007_020a0884;
    }
    if (outCleared != NULL) {
        *outCleared = 0;
    }
    if (outHandler != NULL) {
        *(void **)outHandler = handler;
    }
}
