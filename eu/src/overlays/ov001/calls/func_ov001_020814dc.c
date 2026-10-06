#include "nitro/types.h"

extern u32 VEC_Add();

void
func_ov001_020814dc(int self, u32 value)
{
    VEC_Add(self + 0x40, value, self + 0x78);
}
