#include "nitro/types.h"

extern s32 IsScreenModeIdle(void);
extern void SetFieldStateValue(u32 a, u32 b);
extern void MarkFieldValueNegative(void);

u32 func_ov030_020ba90c(void)
{
    s32 ready;

    ready = IsScreenModeIdle();
    if (ready != 0) {
        SetFieldStateValue(0xfffffffd, 3);
        MarkFieldValueNegative();
        return 7;
    }
    return 0xffffffff;
}
