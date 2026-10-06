#include "nitro/types.h"

extern void ActorSlot_UnlinkRoot(void *object);

void func_ov041_020ce200(u8 *owner) {
    ActorSlot_UnlinkRoot(owner + 0x1c00);
}
