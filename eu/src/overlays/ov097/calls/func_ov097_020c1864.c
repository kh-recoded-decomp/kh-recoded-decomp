#include "nitro/types.h"

typedef struct SpriteSlot {
    u8 pad_00[40];
    void *resource;
} SpriteSlot;

extern void MI_CpuFill8(void *dst, int value, int size);
extern void *Archive_LoadFile(u32 fileId, u32 flags);
extern void RebindSpriteToCell(SpriteSlot *slot, int freeResource, int stopAnimation, u32 cellIndex);

BOOL func_ov097_020c1864(SpriteSlot *slot, u32 fileId)
{
    MI_CpuFill8(slot, 0, sizeof(SpriteSlot));
    slot->resource = Archive_LoadFile(fileId, 0x11);
    RebindSpriteToCell(slot, 1, 1, 0);
    return TRUE;
}
