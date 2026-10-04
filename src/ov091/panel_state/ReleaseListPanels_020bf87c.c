#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
} MenuScene;

extern void Slot_UnlinkAll_0204f104(void *objManager);
extern void Obj_Release_0204eff8(void *objManager);

void ReleaseListPanels_020bf87c(MenuScene *scene)
{
    void *bottom = scene->screenObjects[1];

    Slot_UnlinkAll_0204f104(bottom);
    Obj_Release_0204eff8(bottom);
    Slot_UnlinkAll_0204f104(scene->screenObjects[0]);
    Obj_Release_0204eff8(scene->screenObjects[0]);
}
