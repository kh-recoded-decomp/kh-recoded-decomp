#include "nitro/types.h"

extern u32 func_ov001_0207a8fc(s32 panel);
extern void MarkMapMenuDirty(void);

extern u32 data_ov001_020a04e8;

void func_ov001_0207b4e8(void)
{
    u32 ready;

    ready = func_ov001_0207a8fc(data_ov001_020a04e8);
    if (ready != 0) {
        MarkMapMenuDirty();
    }
}
