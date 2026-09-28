#include "nitro/types.h"

extern void func_01ff8830(void *dest, u32 value, u32 size);

void ZeroBytes0x28_020ac0f8(void *obj)
{
    func_01ff8830(obj, 0, 0x28);
}
