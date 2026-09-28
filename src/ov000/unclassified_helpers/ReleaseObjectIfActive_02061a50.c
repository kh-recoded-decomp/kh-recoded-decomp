#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x224];
    u8 object[0x6658 - 0x224];
    u32 active;
} Owner;

extern int Obj_Release_0204eff8(void *object);

void ReleaseObjectIfActive_02061a50(Owner *owner)
{
    if (owner->active == 0) {
        return;
    }
    Obj_Release_0204eff8(owner->object);
    owner->active = 0;
}
