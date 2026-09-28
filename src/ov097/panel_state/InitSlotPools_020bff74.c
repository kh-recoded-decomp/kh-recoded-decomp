#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 pad_0000[0x218];
    NNSFndList panelSlots;
    u8 pad_0224[0x664c - 0x224];
    NNSFndList iconSlots;
} MenuScene;

extern void NNS_FndInitListWithOffset0_0204f11c(NNSFndList *list);

void InitSlotPools_020bff74(MenuScene *scene)
{
    NNS_FndInitListWithOffset0_0204f11c(&scene->panelSlots);
    NNS_FndInitListWithOffset0_0204f11c(&scene->iconSlots);
}
