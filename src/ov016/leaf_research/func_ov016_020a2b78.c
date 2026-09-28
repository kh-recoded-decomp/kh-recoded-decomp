#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x58];
    u8 buffer[0xc0 - 0x58];
    u32 flags;
} ObjectState;

extern BOOL func_ov016_020a2a94(ObjectState *obj, u8 *buffer);

BOOL func_ov016_020a2b78(ObjectState *obj)
{
    BOOL result = 0;

    if (((obj->flags & 0x8000) != 0) && (result = func_ov016_020a2a94(obj, obj->buffer), result != 0)) {
        obj->flags &= 0xffff7fff;
    }
    return result;
}
