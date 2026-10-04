#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x200];
    u8 objManagers[2][0x6434];
} SceneWork;

extern void Slot_UnlinkAll_0204f104(void *manager);
extern int Obj_Release_0204eff8(void *manager);

void ReleaseSceneObjManagers_020c02c0(SceneWork *work)
{
    void *second = work->objManagers[1];
    Slot_UnlinkAll_0204f104(second);
    Obj_Release_0204eff8(second);
    Slot_UnlinkAll_0204f104(work->objManagers[0]);
    Obj_Release_0204eff8(work->objManagers[0]);
}
