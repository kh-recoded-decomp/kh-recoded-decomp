#include "nitro/types.h"

extern void ZeroActorTailBlock_02090230(void *block);
extern BOOL ReleaseActorResources_02090240(void *actor);

BOOL HandleActorLifecycleEvent_020998ac(int event, void *actor)
{
    switch (event) {
    case 0:
        ZeroActorTailBlock_02090230(actor);
        break;
    case 1:
        ReleaseActorResources_02090240(actor);
        break;
    }
    return TRUE;
}
