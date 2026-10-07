#include "nitro/types.h"

extern s32 g_stageEventsState;
extern s32 func_ov001_0209c914(s32 first, s32 second, u16 *outResult);

s32 func_ov001_020878c4(s32 first, s32 second, u16 *outResult)
{
    if (g_stageEventsState != -1) {
        return func_ov001_0209c914(first, second, outResult);
    }
    return 0;
}
