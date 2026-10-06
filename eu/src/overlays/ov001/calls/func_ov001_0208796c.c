#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 func_ov001_0209c9c4(s32 startIndex);

s32 func_ov001_0208796c(s32 startIndex)
{
    if (data_ov001_0209f2e8 != -1) {
        return func_ov001_0209c9c4(startIndex);
    }
    return 0;
}
