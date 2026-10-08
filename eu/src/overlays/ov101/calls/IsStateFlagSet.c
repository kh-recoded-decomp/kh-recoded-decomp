#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xC];
    u32 flagSets[3][2];
} Ov101State;

extern Ov101State *data_ov101_020c5920;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsStateFlagSet(int setIndex, int bitIndex)
{
    return GetPackedBitMask(
        data_ov101_020c5920->flagSets[setIndex], bitIndex
    ) != 0;
}
