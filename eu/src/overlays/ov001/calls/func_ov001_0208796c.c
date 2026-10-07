#include "nitro/types.h"

extern s32 g_stageEventsState;
extern s32 func_ov001_0209c9c4(s32 startIndex);

s32 func_ov001_0208796c(s32 startIndex)
{
    if (g_stageEventsState != -1) {
        return func_ov001_0209c9c4(startIndex);
    }
    return 0;
}
