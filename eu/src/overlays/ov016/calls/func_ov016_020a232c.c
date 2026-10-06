#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x30];
    u16 flags;
    u8 pad_032[0x5e];
    s16 index;
} ObjectState;

void func_ov016_020a232c(ObjectState *obj)
{
    if (obj->index != -1) {
        obj->flags &= 0xffef;
        return;
    }
    obj->flags |= 0x10;
}
