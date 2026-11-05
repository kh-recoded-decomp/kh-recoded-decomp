#include "nitro/types.h"

s32 GetStageListFirstOrNull(u8 *obj)
{
    s32 result;
    if ((obj == 0) || (result = *(s32 *)(obj + 8), result == 0)) {
        result = 0;
    }
    return result;
}
