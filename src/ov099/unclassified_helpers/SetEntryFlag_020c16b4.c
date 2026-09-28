#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
} SceneWork;

extern SceneWork *g_sceneWork_020c28e0;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c16b4(int flagSet, int entryIndex)
{
    SetPackedBit(g_sceneWork_020c28e0->entryFlags[flagSet], entryIndex);
}
