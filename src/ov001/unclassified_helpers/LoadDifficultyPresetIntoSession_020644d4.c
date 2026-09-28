#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u8 *data_0205fe0c;
extern int func_02027348(int address, int count);
extern void func_01ff878c(void *dst, void *src, u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);

void LoadDifficultyPresetIntoSession_020644d4(void)
{
    u32 sessionBase = data_ov001_020a0460;
    int mode = func_02027348(0x1a00, 2);

    if (mode != 3)
    {
        int offset = mode * 0xf00 + 0x3300;
        func_01ff878c(data_0205fe0c + (offset / 32) * 4, (void *)(sessionBase + 0x28), 0x1e0);
        return;
    }
    func_01ff8740(0, (void *)(sessionBase + 0x28), 0x1e0);
}
