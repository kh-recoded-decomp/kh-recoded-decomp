#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *g_menuScene_020c0700;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c01ac(int flagSet, int entryIndex)
{
    SetPackedBit(&g_menuScene_020c0700->entryFlags[flagSet], entryIndex);
}
