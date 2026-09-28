#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x180];
    u8 slotPool[1];
} SlotPoolOwner;

extern void Slot_UnlinkAll_0204f104(void *pool);
extern int Obj_Release_0204eff8(void *object);

void ReleaseSlotPool_020c01ac(SlotPoolOwner *owner)
{
    Slot_UnlinkAll_0204f104(owner->slotPool);
    Obj_Release_0204eff8(owner->slotPool);
}
