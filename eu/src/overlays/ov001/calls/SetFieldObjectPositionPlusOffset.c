#include "nitro/types.h"

extern u32 VEC_Add();

void
SetFieldObjectPositionPlusOffset(int self, u32 value)
{
    VEC_Add(self + 0x40, value, self + 0x78);
}
