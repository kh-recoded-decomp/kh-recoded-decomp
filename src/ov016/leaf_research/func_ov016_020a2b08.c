#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x48];
    u8 buffer[8];
} ObjectState;

extern void func_ov016_020a2a74(ObjectState *obj, u8 *buffer, u32 count, u32 size, u32 flags);

void func_ov016_020a2b08(ObjectState *obj)
{
    func_ov016_020a2a74(obj, obj->buffer, 8, 0x1000, 0);
}
