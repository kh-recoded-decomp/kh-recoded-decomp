#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
} SceneWork;

extern SceneWork *g_sceneWork_020c28e0;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c168c(int flagSet, int entryIndex)
{
    return GetPackedBitMask(g_sceneWork_020c28e0->entryFlags[flagSet], entryIndex) != 0;
}
