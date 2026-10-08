#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct SpriteTexture {
    u32 unknown_00;
    u32 texParams[2];
} SpriteTexture;

typedef struct SpriteRegion {
    SpriteTexture *texture;
    s16 x;
    s16 y;
    fx32 depth;
    u16 u;
    u16 v;
    u16 width;
    u16 height;
    u16 palette;
} SpriteRegion;

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

extern const MtxFx33 data_ov077_020ca174;
#ifndef G3D_BASE_ROT
extern MtxFx33 data_0205a9b8;
#define G3D_BASE_ROT data_0205a9b8
#endif
#ifndef G3D_FLAGS
extern GeometryState data_0205a9a4;
#define G3D_FLAGS data_0205a9a4.flags
#endif
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    QueueOrSendGeometryCommand_01ffa37c(op, &param, 1);
}

static inline void GeTexCoord(fx32 s, fx32 t)
{
    u32 data = (u16)(fx16)(s >> 8) | ((u16)(fx16)(t >> 8) << 16);
    QueueOrSendGeometryCommand_01ffa37c(0x22, &data, 1);
}

static inline void GeVtx(fx16 x, fx16 y, fx16 z)
{
    u32 data[2];
    data[0] = (u16)x | ((u16)y << 16);
    data[1] = (u16)z;
    QueueOrSendGeometryCommand_01ffa37c(0x23, data, 2);
}

void DrawSpriteRegionQuad_020c6a8c(const SpriteRegion *region, BOOL highlighted)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov077_020ca174;
    fx32 u;
    fx32 v;
    u32 polygonId;

    scale.x = region->width << 12;
    scale.y = region->height << 12;
    scale.z = FX32_ONE;
    trans.x = (region->x << 12) + (region->width << 11);
    trans.y = (192 << 12) - ((region->y << 12) + (region->height << 11));
    trans.z = region->depth;
    if (region->y <= 0) {
        scale.y += FX32_ONE;
    }
    func_0201931c(&scale);
    func_020192ec(&trans);
    MI_Copy36B_01ff87c4(&rot, &G3D_BASE_ROT);
    G3D_FLAGS &= ~0xa4;
    FlushGeometryState_02019230();
    u = region->u << 12;
    v = region->v << 12;
    scale.x += u;
    scale.y += v;
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, region->texture->texParams, 2);
    polygonId = 2;
    if (!highlighted) {
        polygonId = 0;
    }
    GeCommand1(0x29, 0x1f08c0 | (polygonId << 4));
    GeCommand1(0x20, region->palette);
    GeCommand1(0x40, 1);
    GeTexCoord(u, v);
    GeVtx(-0x800, 0x800, 0);
    GeTexCoord(scale.x, v);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(scale.x, scale.y);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(u, scale.y);
    GeVtx(-0x800, -0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
