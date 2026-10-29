#include "src/overlays/ov041/StageModelRender.h"

void DrawStagePrimaryModel(StageFollowerActor *actor)
{
    StageWork *work = gMovieContextState->stageWork;

    if (actor == &work->weapon) {
        MtxFx43 *matrix = &work->weapon.matrix;
        fx32 scale = actor->node.renderObject.model->positionScale;
        VecFx32 scaling = {scale, scale, scale};

        NNS_G3dGeBufferOP_N(0x1b, &scaling, 3);
        NNS_G3dGlbFlushP();
        if (actor->node.flags & 0x40) {
            setMaterialColorScale(actor->node.colorScale);
        }
        NNS_G3dGeBufferOP_N(0x17, matrix, 12);
        NNS_G3dDraw(&actor->node.renderObject);
    }
}
