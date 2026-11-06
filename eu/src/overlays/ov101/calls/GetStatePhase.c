#include "src/overlays/ov101/ListSceneState.h"

extern ListSceneState *gListMenuGlobalStorage;

u32 GetStatePhase(void)
{
    return gListMenuGlobalStorage->handlerPhase;
}
