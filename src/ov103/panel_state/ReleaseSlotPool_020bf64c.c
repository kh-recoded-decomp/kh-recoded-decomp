#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 slotPool[1];
} MenuScene;

extern void Slot_UnlinkAll_0204f104(void *pool);
extern int Obj_Release_0204eff8(void *object);

void ReleaseSlotPool_020bf64c(MenuScene *scene)
{
    Slot_UnlinkAll_0204f104(scene->slotPool);
    Obj_Release_0204eff8(scene->slotPool);
}
