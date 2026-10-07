#include "nitro/types.h"

typedef struct UnlockEntry {
    u8 flagIndex;
    u8 pad_01[11];
} UnlockEntry;

extern const UnlockEntry gUnlockNoticeEntries[];
extern BOOL IsGlobalPackedBitSet(u32 bitIndex);
extern void SetGlobalPackedBit(u32 bitIndex);

BOOL CheckOrMarkUnlockNoticeSeen(int unlockId, BOOL queryOnly)
{
    u8 flagIndex = gUnlockNoticeEntries[unlockId].flagIndex;
    BOOL isSet = IsGlobalPackedBitSet(flagIndex + 0xf50);
    BOOL seen = TRUE;

    if (!isSet) {
        seen = FALSE;
    }

    if (!seen && !queryOnly) {
        u32 bitIndex;

        asm {
            mov bitIndex, #0xf5
            lsl bitIndex, bitIndex, #4
        }
        SetGlobalPackedBit(flagIndex + bitIndex);
    }
    return seen;
}
