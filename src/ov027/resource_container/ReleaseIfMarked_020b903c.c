#include "nitro/types.h"

typedef struct ReleaseOwner {
    u8 pad_0000[0x6478];
    u32 flags;
} ReleaseOwner;

extern void Obj_Release_0204eff8(void *obj);

void ReleaseIfMarked_020b903c(ReleaseOwner *owner)
{
    if (((owner->flags << 29) >> 31) == 1) {
        Obj_Release_0204eff8(owner);
        owner->flags &= ~4;
    }
}
