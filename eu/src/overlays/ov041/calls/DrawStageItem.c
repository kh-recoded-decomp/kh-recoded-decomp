#include "nitro/types.h"
#include "src/overlays/ov041/StageModelRender.h"

extern void SceneNode_Draw(void *node);

/*
 * Draws an item: with its own scale and 4x3 matrix when it has one, as a plain scene node otherwise. A hidden
 * item is cleared instead and FALSE returned.
 */
BOOL DrawStageItem(StageResourceItem *item)
{
    if (!(item->flags & STAGE_ITEM_VISIBLE)) {
        item->flags = 0;
        return FALSE;
    }
    if (item->flags & STAGE_ITEM_OWN_MATRIX) {
        fx32 scale = item->model.renderObject.model->positionScale;
        VecFx32 scaling = {scale, scale, scale};

        NNS_G3dGeBufferOP_N(0x1b, &scaling, 3);
        NNS_G3dGlbFlushP();
        if (item->model.flags & STAGE_MODEL_COLOR_SCALE) {
            func_01fff67c(item->model.colorScale);
        }
        NNS_G3dGeBufferOP_N(0x17, &item->model.rotation, 12);
        NNS_G3dDraw(&item->model.renderObject);
    } else {
        SceneNode_Draw(&item->model);
    }
    return TRUE;
}
