#include "nitro/types.h"

extern u32 IsGlobalPackedBitSet();
extern u32 func_ov001_0207f71c();

void
func_ov001_02081d6c(int self)
{
    int result;

    if ((*(char *)(self + 0x59) == '\x01') &&
        (result = IsGlobalPackedBitSet(*(char *)(self + 0x5a) + 0x580), result != 0)) {
        func_ov001_0207f71c(self, 0);
    }
}
