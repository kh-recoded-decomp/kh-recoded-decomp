#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 StartStageEventInstance(s32 eventIndex, s32 first, s32 second, u16 *outResult);

s32 func_ov001_020878e0(s32 eventIndex, s32 first, s32 second, u16 *outResult)
{
    if (data_ov001_0209f2e8 != -1) {
        return StartStageEventInstance(eventIndex, first, second, outResult);
    }
    return 0;
}
