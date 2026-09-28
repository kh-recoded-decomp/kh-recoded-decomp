#include "nitro/types.h"

extern u32 func_01ff9e0c();

void
func_ov001_020814b4(int self, u32 value)
{
    func_01ff9e0c(self + 0x40, value, self + 0x78);
}
