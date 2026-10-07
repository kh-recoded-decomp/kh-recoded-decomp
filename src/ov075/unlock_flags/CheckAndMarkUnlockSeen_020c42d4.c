#include "nitro/types.h"

#pragma opt_common_subs off

typedef struct UnlockEntry {
    u8 flagIndex;
    u8 pad_01[0xb];
} UnlockEntry;

extern const UnlockEntry data_ov075_020d1560[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);

static inline BOOL IsUnlockSeen(u8 flagIndex)
{
    return IsGlobalPackedBitSet_02027304(flagIndex + 0xf50);
}

static inline void MarkUnlockSeen(u8 flagIndex)
{
    SetGlobalPackedBit_02027320(flagIndex + 0xf50);
}

BOOL CheckAndMarkUnlockSeen_020c42d4(int index, BOOL peekOnly)
{
    u8 flagIndex = data_ov075_020d1560[index].flagIndex;
    BOOL seen = IsUnlockSeen(flagIndex) ? TRUE : FALSE;

    if (!seen && !peekOnly) {
        MarkUnlockSeen(flagIndex);
    }
    return seen;
}
