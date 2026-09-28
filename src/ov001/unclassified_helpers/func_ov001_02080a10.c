#include "nitro/types.h"

extern u32 func_01ffb2f8();

void
func_ov001_02080a10(int self, u32 value)
{
    u32 slot = 0;

    do {
        if (*(s16 *)(self + (slot & 0xffff) * 2 + 0xd8) > 0) {
            func_01ffb2f8(self, slot & 0xffff, value);
        }
        slot = slot + 1;
    } while ((int)slot < 5);
}
