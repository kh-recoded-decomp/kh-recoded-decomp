#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int *bits;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void SetPackedBit(int *bitWords, int bitIndex);

void SetGlobalPackedBit_02027320(int bitIndex)
{
    SetPackedBit(g_cardThreadState_0205fe00.bits, bitIndex);
}
