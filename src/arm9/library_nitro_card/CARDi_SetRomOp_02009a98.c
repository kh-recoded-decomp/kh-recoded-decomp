#include "nitro/types.h"

#define REG_MCCNT0 (*(vu16 *)0x040001a0)
#define REG_MCCMD0 (*(vu32 *)0x040001a8)
#define REG_MCCMD1 (*(vu32 *)0x040001ac)
#define REG_MCCNT1 (*(vu32 *)0x040001a4)

static inline u32 ByteSwap32(u32 value)
{
    return ((value & 0xff000000) >> 24) | ((value & 0x00ff0000) >> 8) | ((value & 0x0000ff00) << 8) | (value << 24);
}

void CARDi_SetRomOp_02009a98(u32 command, u32 offset)
{
    u32 high = (offset >> 8) | (command << 24);
    u32 low = offset << 24;

    while (REG_MCCNT1 & 0x80000000) {
    }
    REG_MCCNT0 = (u16)((REG_MCCNT0 & ~0x2000) | 0xc000);
    REG_MCCMD0 = ByteSwap32(high);
    REG_MCCMD1 = ByteSwap32(low);
}
