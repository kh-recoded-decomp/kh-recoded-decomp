#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct NNSG3dResMdl NNSG3dResMdl;

typedef struct G3dGlobalState {
    u8 pad_00[0x94];
    MtxFx33 baseRot;
    VecFx32 baseTrans;
    VecFx32 baseScale;
    u32 unk_D0;
    u32 flags;
} G3dGlobalState;

typedef struct ShadowVolume {
    VecFx32 position;
    fx32 scale;
    NNSG3dResMdl **modelRef;
    u8 alpha;
    u8 pad_15;
    u16 rotY;
} ShadowVolume;

extern G3dGlobalState g_g3dGlobal_0205a924;
extern const fx16 g_sinTable_0205356c[];

extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_02019188(void);
extern void SetMaterialPolygonId_0201a5d4(NNSG3dResMdl *model, u32 matId, int polygonId);
extern void SetMaterialCullMode_0201a55c(NNSG3dResMdl *model, u32 matId, int cullMode);
extern void SetMaterialAlpha_0201a64c(NNSG3dResMdl *model, u32 matId, int alpha);
extern void SetMaterialPolygonMode_0201a4e4(NNSG3dResMdl *model, u32 matId, int polygonMode);
extern void NNS_G3dDraw1Mat1Shp_01fff3dc(const NNSG3dResMdl *model, u32 materialId, u32 shapeId, BOOL sendMaterial);

void ShadowVolume_Draw_02036b80(ShadowVolume *shadow)
{
    NNSG3dResMdl *model = *shadow->modelRef;
    int angle;

    if (model == NULL) {
        return;
    }
    g_g3dGlobal_0205a924.baseScale.x = g_g3dGlobal_0205a924.baseScale.y = g_g3dGlobal_0205a924.baseScale.z = shadow->scale;
    g_g3dGlobal_0205a924.baseTrans = shadow->position;
    angle = shadow->rotY >> 4;
    MTX_RotY33_01ff923c(&g_g3dGlobal_0205a924.baseRot, g_sinTable_0205356c[angle],
                        g_sinTable_0205356c[(0x400 - angle) & 0xfff]);
    g_g3dGlobal_0205a924.flags &= ~0xa4;
    func_02019188();

    SetMaterialPolygonId_0201a5d4(model, 0, 0);
    SetMaterialCullMode_0201a55c(model, 0, 1);
    SetMaterialAlpha_0201a64c(model, 0, shadow->alpha);
    SetMaterialPolygonMode_0201a4e4(model, 0, 3);
    NNS_G3dDraw1Mat1Shp_01fff3dc(model, 0, 0, TRUE);

    SetMaterialPolygonId_0201a5d4(model, 0, 0x3f);
    SetMaterialCullMode_0201a55c(model, 0, 3);
    SetMaterialAlpha_0201a64c(model, 0, shadow->alpha);
    SetMaterialPolygonMode_0201a4e4(model, 0, 3);
    NNS_G3dDraw1Mat1Shp_01fff3dc(model, 0, 0, TRUE);

    g_g3dGlobal_0205a924.baseScale.x = g_g3dGlobal_0205a924.baseScale.y = g_g3dGlobal_0205a924.baseScale.z = FX32_ONE;
    g_g3dGlobal_0205a924.flags &= ~0xa4;
}
