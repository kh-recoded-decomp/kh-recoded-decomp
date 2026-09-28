#include "nitro/types.h"

extern void func_01ff8830(void *dest, u32 value, u32 size);

void ZeroAndSetField0xd4_020ac150(void *obj)
{
    func_01ff8830(obj, 0, 0xdc);
    *(u32 *)((u8 *)obj + 0xd4) = 1;
}
