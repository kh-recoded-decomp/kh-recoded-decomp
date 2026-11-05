#include "nitro/types.h"

BOOL IsOv071BossTaskId110(s32 *value)
{
    if (*value == 0x110) {
        return 1;
    }
    return 0;
}
