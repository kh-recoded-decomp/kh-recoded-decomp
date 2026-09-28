#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 slotPool[1];
} MenuScene;

extern void NNS_FndInitListWithOffset0_0204f11c(void *list);

void InitSlotPool_020bf668(MenuScene *scene)
{
    NNS_FndInitListWithOffset0_0204f11c(scene->slotPool);
}
