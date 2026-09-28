#include "nitro/types.h"

extern void func_02028448(void *state, int page);

void func_0202849c(void *state, int page, int delta)
{
    *(s32 *)((u8 *)state + 0x14 + page * 0x18) += delta * 2;
    func_02028448(state, page);
    *(s32 *)((u8 *)state + 0x14 + page * 0x18) -= delta * 2;
}
