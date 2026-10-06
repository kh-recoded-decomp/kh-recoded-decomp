#include "nitro/types.h"

extern int IsScreenModeIdle();
extern void SetFieldStateValue();
extern void MarkFieldValueNegative();

u32 func_ov040_020bd5e0(void)
{
    int ready;

    ready = IsScreenModeIdle();
    if (ready != 0) {
        SetFieldStateValue(0xfffffffd, 3);
        MarkFieldValueNegative();
        return 5;
    }
    return 0xffffffff;
}
