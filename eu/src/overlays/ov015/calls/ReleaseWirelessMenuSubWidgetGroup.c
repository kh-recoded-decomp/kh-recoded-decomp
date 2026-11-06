#include "nitro/types.h"

typedef struct {
    u8 pad0_4 : 5;
    u8 flag5 : 1;
    u8 pad6_7 : 2;
} PanelFlagsE0b;

extern void *gWirelessMenuWork;
extern void FreeTagTrackerPools(void *block);
extern void DestroyObjectsAndRelease(void *block);

void ReleaseWirelessMenuSubWidgetGroup(void) {
    PanelFlagsE0b *flags = (PanelFlagsE0b *)((u8 *)gWirelessMenuWork + 0xe0);
    if (flags->flag5 == 0) {
        return;
    }
    flags->flag5 = 0;
    FreeTagTrackerPools((u8 *)gWirelessMenuWork + 0x5f8);
    DestroyObjectsAndRelease((u8 *)gWirelessMenuWork + 0x6ac0);
}
