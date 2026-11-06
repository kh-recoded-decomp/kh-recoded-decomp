#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xC];
    u32 flagSets[3][2];
} Ov101State;

extern Ov101State *gListMenuGlobalStorage;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsStateFlagSet(int setIndex, int bitIndex)
{
    return GetPackedBitMask(
        gListMenuGlobalStorage->flagSets[setIndex], bitIndex
    ) != 0;
}
