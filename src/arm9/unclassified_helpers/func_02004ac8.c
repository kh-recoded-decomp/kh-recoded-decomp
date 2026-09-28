#include "nitro/types.h"

extern void func_01ff89a8(const void *src, void *dest, u32 size);
extern u8 g_smallBuffer_02fffcf4[6];

void func_02004ac8(void *dest)
{
    func_01ff89a8(g_smallBuffer_02fffcf4, dest, 6);
}
