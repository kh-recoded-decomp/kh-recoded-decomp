#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern u32 func_0201f154(u32 value);

int CacheSeqArcStatus_0204e00c(int index)
{
    u8 *ctx = g_soundWork_0206084c;
    u32 status = func_0201f154(*(u32 *)(g_soundWork_0206084c + 0xb04b4));
    *(u32 *)(ctx + index * 4 + 0xa8) = status;
    return (int)(s8)status;
}
