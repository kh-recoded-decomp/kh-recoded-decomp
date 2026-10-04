#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int unlockBit;
    u8 pad_30[4];
} MenuEntryDef;

typedef struct {
    u8 pad_0000[0xf0cc];
    int lastUnlockedEntry;
} MenuScene;

extern MenuEntryDef data_ov097_020c2124[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void SetEntryFlag_020c14a0(int flagSet, int entryIndex);

void SyncUnlockedEntryFlags_020c14c0(MenuScene *scene)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (IsGlobalPackedBitSet_02027304(data_ov097_020c2124[i].unlockBit)) {
            SetEntryFlag_020c14a0(0, i);
            scene->lastUnlockedEntry = i + 1;
            SetGlobalPackedBit_02027320(i + 0x11b2);
        }
        if (!IsGlobalPackedBitSet_02027304(i + 0x1262) && IsGlobalPackedBitSet_02027304(i + 0x11b2)) {
            SetEntryFlag_020c14a0(1, i);
        }
    }
}
