#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} ObjManager;

typedef struct {
    u8 pad_000[0x45c];
    ObjManager objManagers[2];
} SceneWork;

extern void Slot_UnlinkAll_0204f104(void *manager);
extern int Obj_Release_0204eff8(void *manager);

void ReleaseObjManagers_020c07c8(SceneWork *work)
{
    ObjManager *manager;

    manager = &work->objManagers[1];
    Slot_UnlinkAll_0204f104(manager);
    Obj_Release_0204eff8(manager);
    manager = &work->objManagers[0];
    Slot_UnlinkAll_0204f104(manager);
    Obj_Release_0204eff8(manager);
}
