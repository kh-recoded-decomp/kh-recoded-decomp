#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 *bits;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern u32 ReadPackedBitField_0202d4c4(u32 *words, u32 startBit, u32 fieldWidth);

u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount)
{
    return ReadPackedBitField_0202d4c4(g_cardThreadState_0205fe00.bits, bitOffset, bitCount);
}
