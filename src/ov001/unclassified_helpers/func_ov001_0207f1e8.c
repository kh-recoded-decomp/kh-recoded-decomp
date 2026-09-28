#include "nitro/types.h"

extern u32 func_0202a1c4();

void
func_ov001_0207f1e8(int self)
{
    int work = *(int *)(self + 8);

    if (*(int *)(work + 0x58) != 0) {
        func_0202a1c4();
        *(u32 *)(work + 0x58) = 0;
    }
    if (*(int *)(work + 0x60) != 0) {
        func_0202a1c4();
        *(u32 *)(work + 0x60) = 0;
    }
}
