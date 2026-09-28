#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int *bits;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

BOOL IsGlobalPackedBitSet_02027304(int bitIndex)
{
    if (GetPackedBitMask(g_cardThreadState_0205fe00.bits, bitIndex) != 0) {
        return TRUE;
    }
    return FALSE;
}
