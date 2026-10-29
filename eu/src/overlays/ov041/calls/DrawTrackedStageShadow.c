#include "src/overlays/ov041/StageModelRender.h"

void DrawTrackedStageShadow(StageFollowerActor *actor)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;

    for (i = 0; i < 2; ++i) {
        StageFollowerActor *tracked = work->shadowActors[i];
        if (tracked == actor) {
            if (!(tracked->stateFlags & 1)) {
                tracked->stateFlags = tracked->stateFlags & 0xfd;
            }
            if (tracked->stateFlags & 2) {
                fx32 scale = actor->node.renderObject.model->positionScale;
                VecFx32 scaling = {scale, scale, scale};

                NNS_G3dGeBufferOP_N(0x1b, &scaling, 3);
                NNS_G3dGlbFlushP();
                if (actor->node.flags & 0x40) {
                    setMaterialColorScale(actor->node.colorScale);
                }
                NNS_G3dGeBufferOP_N(0x17, &tracked->matrix, 12);
                NNS_G3dDraw(&actor->node.renderObject);
            }
            return;
        }
    }
}
