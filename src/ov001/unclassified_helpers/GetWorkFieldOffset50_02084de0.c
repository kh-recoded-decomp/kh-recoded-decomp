#include "nitro/types.h"

u32
GetWorkFieldOffset50_02084de0(int self)
{
    int work = *(int *)(self + 8);
    return *(u32 *)(work + 0x50);
}
