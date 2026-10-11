#include "src/overlays/ov101/ListSceneState.h"

extern ListSceneState *data_ov101_020c5920;
extern void RuntimeState_SetCondition(BOOL condition);

void CommitPageInteractionBounds(ListSceneState *scene)
{
    PageInteractionBounds *bounds;
    PageInteractionClip *clip;
    ListSceneState *global;
    scene->interactionActive = FALSE;
    RuntimeState_SetCondition(TRUE);
    global = data_ov101_020c5920;
    clip = &global->interactionClip;
    bounds = &scene->interactionBounds;
    clip->maxX = bounds->originX + bounds->maxX;
    clip->maxY = bounds->originY + bounds->maxY;
    global->interactionClip.minX = bounds->originX + bounds->minX;
    clip->minY = bounds->originY + bounds->minY;
}
