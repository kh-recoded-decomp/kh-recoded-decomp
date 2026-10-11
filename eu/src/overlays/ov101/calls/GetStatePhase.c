#include "src/overlays/ov101/ListSceneState.h"

extern ListSceneState *data_ov101_020c5920;

u32 GetStatePhase(void)
{
    return data_ov101_020c5920->handlerPhase;
}
