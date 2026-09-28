#include "nitro/types.h"

extern u32 func_02027304();
extern u32 func_ov001_0207f6f4();

void
func_ov001_02081d44(int self)
{
    int result;

    if ((*(char *)(self + 0x59) == '\x01') &&
        (result = func_02027304(*(char *)(self + 0x5a) + 0x580), result != 0)) {
        func_ov001_0207f6f4(self, 0);
    }
}
