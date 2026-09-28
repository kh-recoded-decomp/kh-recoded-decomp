#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 *bits;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void WritePackedBits_0202d560(u32 *base, u32 bitOffset, u32 bitCount, u32 value);

void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value)
{
    WritePackedBits_0202d560(g_cardThreadState_0205fe00.bits, bitOffset, bitCount, value);
}
