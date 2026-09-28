#include "nitro/types.h"

#define GLOBAL_FLAG_BANK_BASE 0xf50

extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void ClearGlobalPackedBit_02027334(int bitIndex);

void WriteGlobalPackedFlag_020679dc(int flagIndex, BOOL enabled)
{
    if (enabled) {
        SetGlobalPackedBit_02027320(flagIndex + GLOBAL_FLAG_BANK_BASE);
        return;
    }
    ClearGlobalPackedBit_02027334(flagIndex + GLOBAL_FLAG_BANK_BASE);
}
