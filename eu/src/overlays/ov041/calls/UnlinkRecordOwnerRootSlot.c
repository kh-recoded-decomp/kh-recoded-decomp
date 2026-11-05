#include "nitro/types.h"

extern void ActorSlot_UnlinkRoot(void *object);

void UnlinkRecordOwnerRootSlot(u8 *owner) {
    ActorSlot_UnlinkRoot(owner + 0x1c00);
}
