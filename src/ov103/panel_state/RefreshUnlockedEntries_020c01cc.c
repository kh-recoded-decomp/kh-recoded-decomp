#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetEntryFlag_020c01ac(int flagSet, int entryIndex);

void RefreshUnlockedEntries_020c01cc(void)
{
    int i;
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 10:
            if (IsGlobalPackedBitSet_02027304(0xf4c) || IsGlobalPackedBitSet_02027304(0x1150)) {
                SetEntryFlag_020c01ac(0, i);
            }
            if ((IsGlobalPackedBitSet_02027304(0xf4c) || IsGlobalPackedBitSet_02027304(0x1150)) && !IsGlobalPackedBitSet_02027304(0xf4e)) {
                SetEntryFlag_020c01ac(1, i);
            }
            break;
        case 8:
            if (IsGlobalPackedBitSet_02027304(0xf4d) || IsGlobalPackedBitSet_02027304(0x1151)) {
                SetEntryFlag_020c01ac(0, i);
            }
            if (IsGlobalPackedBitSet_02027304(0xf4d) || IsGlobalPackedBitSet_02027304(0x1151)) {
                IsGlobalPackedBitSet_02027304(0xf4f);
            }
            break;
        default:
            if (IsGlobalPackedBitSet_02027304(0xbea)) {
                SetEntryFlag_020c01ac(0, i);
            }
            break;
        }
    }
}
