#include "nitro/types.h"

typedef struct ObjectState {
    u8 pad_000[0x68];
    void (*callback)(struct ObjectState *self);
    u8 pad_06c[0x54];
    u32 flags;
} ObjectState;

void func_ov016_020a6974(ObjectState *obj, void (*callback)(ObjectState *self))
{
    obj->callback = callback;
    obj->flags |= 0x80;
}
