#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern s32 AreAllListNodesReady(void);
extern void func_ov001_020871a0(s32 value);

u32 func_ov028_020ba720(void)
{
    s32 value = AreAllListNodesReady();

    if (value != 0) {
        func_ov001_020871a0(value);
        *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x8000;
        return 3;
    }
    return 0xffffffff;
}
