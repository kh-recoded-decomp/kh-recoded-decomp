#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    u8 pad_0000[0x6400];
    NNSFndList slots;
} IconArea;

typedef struct {
    u8 pad_0000[0x218];
    NNSFndList panelSlots;
    u8 pad_0224[0x24c - 0x224];
    IconArea iconArea;
} MenuScene;

extern void Slot_UnlinkAll_0204f104(void *list);
extern int Obj_Release_0204eff8(void *object);

void ReleaseSlotPools_020bff44(MenuScene *scene)
{
    IconArea *icons = &scene->iconArea;

    Slot_UnlinkAll_0204f104(&icons->slots);
    Obj_Release_0204eff8(&icons->slots);
    Slot_UnlinkAll_0204f104(&scene->panelSlots);
    Obj_Release_0204eff8(&scene->panelSlots);
}
