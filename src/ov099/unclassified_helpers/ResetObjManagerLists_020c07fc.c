#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    NNSFndList activeList;
    u8 pad_0c[0x6434 - 0xc];
} ObjManager;

typedef struct {
    u8 pad_000[0x45c];
    ObjManager objManagers[2];
} SceneWork;

extern void NNS_FndInitListWithOffset0_0204f11c(NNSFndList *list);

void ResetObjManagerLists_020c07fc(SceneWork *work)
{
    NNS_FndInitListWithOffset0_0204f11c(&work->objManagers[0].activeList);
    NNS_FndInitListWithOffset0_0204f11c(&work->objManagers[1].activeList);
}
