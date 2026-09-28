#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xcbc0];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *g_menuScene_020c3720;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c1718(int flagSet, int entryIndex)
{
    SetPackedBit(&g_menuScene_020c3720->entryFlags[flagSet], entryIndex);
}
