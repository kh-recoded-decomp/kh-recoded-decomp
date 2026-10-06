#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 QueryStageEventState(s32 mode, s32 filterId);

s32 func_ov001_02087890(s32 mode)
{
    if (data_ov001_0209f2e8 != -1) {
        return QueryStageEventState(mode, -1);
    }
    return 0;
}
