#include "nitro/types.h"

typedef struct UnlockEntry {
    u8 flagIndex;
    u8 pad_01[11];
} UnlockEntry;

extern const UnlockEntry gUnlockNoticeEntries[];
extern BOOL IsGlobalPackedBitSet(u32 bitIndex);
extern void SetGlobalPackedBit(u32 bitIndex);

#pragma opt_common_subs off
BOOL CheckOrMarkUnlockNoticeSeen(int unlockId, BOOL queryOnly)
{
    u8 flagIndex = gUnlockNoticeEntries[unlockId].flagIndex;
    BOOL isSet = IsGlobalPackedBitSet(flagIndex + 0xf50);
    BOOL seen = TRUE;

    if (!isSet) {
        seen = FALSE;
    }

    if (!seen && !queryOnly) {
        SetGlobalPackedBit(flagIndex + 0xf50);
    }
    return seen;
}
#pragma opt_common_subs on
