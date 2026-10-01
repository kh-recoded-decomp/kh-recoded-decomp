#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x1e];
    u8 renderObj[0x5c];
    u16 angleY;
    u16 angleX;
    MtxFx43 matrix;
    VecFx32 position;
    u8 pad_bc[0x40];
    u16 colorScale;
} SceneNode;

typedef struct GeometryStateCache {
    u8 pad_00[0x54];
    u32 flags;
} GeometryStateCache;

extern VecFx32 data_0205a9e8;
extern MtxFx43 data_0205a9b8;
extern GeometryStateCache data_0205a9a4;
extern void func_ov001_0208f3c4(SceneNode *node);
extern void FlushGeometryStateVariant_020191b8(void);
extern void setMaterialColorScale_01fff67c(int packedRgb);
extern void func_01ffe1bc(void *renderObj);

void SceneNode_DrawImmediate_0208f4f4(SceneNode *node) {
    data_0205a9e8 = node->position;
    func_ov001_0208f3c4(node);
    data_0205a9b8 = node->matrix;
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryStateVariant_020191b8();
    if (node->flags & 0x40) {
        setMaterialColorScale_01fff67c(node->colorScale);
    }
    func_01ffe1bc(node->renderObj);
}
