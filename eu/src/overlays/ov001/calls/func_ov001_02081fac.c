#include "nitro/types.h"

extern u32 DrawNodeWithExplicitProjection();

void
func_ov001_02081fac(int self)
{
    int work = *(int *)(self + 8);

    DrawNodeWithExplicitProjection(*(int *)(self + 0xc) + 0x14, work + 0x84, *(int *)(work + 0xc0),
                  -*(int *)(work + 0xc0), -*(int *)(work + 0xbc), *(int *)(work + 0xbc));
}
