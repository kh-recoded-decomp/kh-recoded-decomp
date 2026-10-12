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
    clip = &global->pageDrag.clip;
    bounds = &scene->interactionBounds;
    clip->minX = bounds->originX + bounds->x1;
    clip->minY = bounds->originY + bounds->y1;
    global->pageDrag.clip.maxX = bounds->originX + bounds->x0;
    clip->maxY = bounds->originY + bounds->y0;
}
