#include "nitro/types.h"

extern u32 func_0202a1c4();

void
func_ov001_0207f244(int self)
{
    if (*(int *)(self + 0x18) != 0) {
        func_0202a1c4();
        *(u32 *)(self + 0x18) = 0;
    }
}
