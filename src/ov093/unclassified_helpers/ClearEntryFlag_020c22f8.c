#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1a0];
    u32 entryFlags[4];
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;
extern void ClearPackedBit(u32 *bitWords, int bitIndex);

void ClearEntryFlag_020c22f8(int flagSet, int entryIndex)
{
    ClearPackedBit(&g_sceneWork_020c50e0->entryFlags[flagSet], entryIndex);
}
