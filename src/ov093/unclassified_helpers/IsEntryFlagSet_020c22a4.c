#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1a0];
    u32 entryFlags[4];
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex)
{
    return GetPackedBitMask(&g_sceneWork_020c50e0->entryFlags[flagSet], entryIndex) != 0;
}
