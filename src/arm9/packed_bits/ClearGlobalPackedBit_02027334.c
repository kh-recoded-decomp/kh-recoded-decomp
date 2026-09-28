#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int *bits;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void ClearPackedBit(int *bitWords, int bitIndex);

void ClearGlobalPackedBit_02027334(int bitIndex)
{
    ClearPackedBit(g_cardThreadState_0205fe00.bits, bitIndex);
}
