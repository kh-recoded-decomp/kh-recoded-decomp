#include "nitro/types.h"

typedef struct {
    s32 unk_00;
    u32 flagSets[3][2];
} Ov101State;

extern Ov101State *g_ov101State_020c4d20;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex)
{
    return GetPackedBitMask(g_ov101State_020c4d20->flagSets[setIndex], bitIndex) != 0;
}
