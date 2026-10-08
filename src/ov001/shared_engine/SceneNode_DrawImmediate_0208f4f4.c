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

#ifdef USE_NNS_G3D_GLB
typedef struct GeometryGlobalState {
    u8 pad_00[0x94];
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
} GeometryGlobalState;

extern GeometryGlobalState NNS_G3dGlb;
#endif

#ifndef G3D_BASE_SCALE
extern VecFx32 data_0205a9e8;
#define G3D_BASE_SCALE data_0205a9e8
#endif
#ifndef G3D_BASE_MATRIX
extern MtxFx43 data_0205a9b8;
#define G3D_BASE_MATRIX data_0205a9b8
#endif
#ifndef G3D_FLAGS
extern GeometryStateCache data_0205a9a4;
#define G3D_FLAGS data_0205a9a4.flags
#endif
extern void func_ov001_0208f3c4(SceneNode *node);
extern void FlushGeometryStateVariant_020191b8(void);
extern void setMaterialColorScale_01fff67c(int packedRgb);
extern void func_01ffe1bc(void *renderObj);

void SceneNode_DrawImmediate_0208f4f4(SceneNode *node) {
    G3D_BASE_SCALE = node->position;
    func_ov001_0208f3c4(node);
    G3D_BASE_MATRIX = node->matrix;
    G3D_FLAGS &= ~0xa4;
    FlushGeometryStateVariant_020191b8();
    if (node->flags & 0x40) {
        setMaterialColorScale_01fff67c(node->colorScale);
    }
    func_01ffe1bc(node->renderObj);
}
