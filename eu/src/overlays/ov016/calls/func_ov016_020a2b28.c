#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x48];
    u8 buffer[8];
} ObjectState;

extern void InitAnimTrack(ObjectState *obj, u8 *buffer, u32 count, u32 size, u32 flags);

void func_ov016_020a2b28(ObjectState *obj)
{
    InitAnimTrack(obj, obj->buffer, 8, 0x1000, 0);
}
