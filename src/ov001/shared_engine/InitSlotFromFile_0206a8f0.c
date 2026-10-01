#include "nitro/types.h"

typedef struct SpriteSlot {
    u8 pad_00[0x2c];
    void *resource;
} SpriteSlot;

extern void func_01ff8830(void *dst, int value, int size);
extern void *func_0202c478(u32 fileId, u32 flags);
extern void RebindSlotTexture_0206a95c(SpriteSlot *slot, int freeResource, int stopAnimation, u32 cellIndex);

BOOL InitSlotFromFile_0206a8f0(SpriteSlot *slot, u32 fileId)
{
    func_01ff8830(slot, 0, sizeof(SpriteSlot));
    slot->resource = func_0202c478(fileId, 0x11);
    RebindSlotTexture_0206a95c(slot, 1, 1, 0);
    return TRUE;
}
