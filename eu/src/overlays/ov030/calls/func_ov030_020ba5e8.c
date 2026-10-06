#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 AreAllListNodesReady(void);
extern void func_ov001_020871a0(void);

u32 func_ov030_020ba5e8(void)
{
    s32 ready;

    ready = AreAllListNodesReady();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_020871a0();
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x8000;
    return 3;
}
