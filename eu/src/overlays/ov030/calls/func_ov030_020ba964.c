#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern void StartIdleSceneObjects(void);
extern void SetFieldObjectInteractionsBlocked(u32 arg);

u32 func_ov030_020ba964(void)
{
    u32 ctx;

    ctx = data_ov030_020bd020;
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x20;
    if ((*(u16 *)(ctx + 6) & 0x10) == 0) {
        StartIdleSceneObjects();
        SetFieldObjectInteractionsBlocked(1);
    }
    return 0xf;
}
