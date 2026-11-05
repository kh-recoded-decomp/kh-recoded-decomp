#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x30];
    u16 flags;
    u8 pad_032[0x5e];
    s16 index;
} ObjectState;

void UpdateFieldObjectDrawFlagFromPreviousLink(ObjectState *obj)
{
    if (obj->index != -1) {
        obj->flags &= 0xffef;
        return;
    }
    obj->flags |= 0x10;
}
