#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *g_menuScene_020c0700;
extern u32 GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c0180(int flagSet, int entryIndex)
{
    return GetPackedBitMask(&g_menuScene_020c0700->entryFlags[flagSet], entryIndex) != 0;
}
