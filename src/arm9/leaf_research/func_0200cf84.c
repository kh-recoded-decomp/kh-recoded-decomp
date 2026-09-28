#include "nitro/types.h"

extern u32 func_0200d280(u32 base, u32 offset, u32 unused1, u32 unused2);
extern void func_01ff89a8(const void *src, void *dst, u32 len);

s32 func_0200cf84(u32 base, const void *src, u32 offset, u32 len)
{
    u32 dst = func_0200d280(base, offset, offset, len);
    func_01ff89a8(src, (void *)dst, len);
    return 0;
}
