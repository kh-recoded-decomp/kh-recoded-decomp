#include "nitro/types.h"

typedef struct ObjectManager {
    u8 pad_000[0x120];
    u32 flagBits;
} ObjectManager;

extern ObjectManager *g_objectManager_020a04d8;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL ObjectManager_IsFlagBitSet_0207f068(int bitIndex)
{
    if (GetPackedBitMask(&g_objectManager_020a04d8->flagBits, bitIndex) != 0) {
        return TRUE;
    }
    return FALSE;
}
