#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u8 *data_0205fe0c;
extern int func_02027348(int address, int count);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void StoreSessionDifficultyPreset_0206452c(void)
{
    u32 sessionBase = data_ov001_020a0460;
    int mode = func_02027348(0x1a00, 2);

    if (mode != 3)
    {
        int offset = mode * 0xf00 + 0x3300;
        func_01ff878c((void *)(sessionBase + 0x28), data_0205fe0c + (offset / 32) * 4, 0x1e0);
    }
}
