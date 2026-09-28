#include "nitro/types.h"

extern void func_01ff89a8(const void *src, void *dst, u32 len);

void func_02028dc4(u16 *state, const void *src)
{
    func_01ff89a8(src, state, 4);
    state[1] = (state[1] & ~1) | 1;
    *state = *state & ~0xffe0;
}
