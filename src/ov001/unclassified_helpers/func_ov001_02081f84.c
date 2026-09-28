#include "nitro/types.h"

extern u32 func_0202f1b0();

void
func_ov001_02081f84(int self)
{
    int work = *(int *)(self + 8);

    func_0202f1b0(*(int *)(self + 0xc) + 0x14, work + 0x84, *(int *)(work + 0xc0),
                  -*(int *)(work + 0xc0), -*(int *)(work + 0xbc), *(int *)(work + 0xbc));
}
