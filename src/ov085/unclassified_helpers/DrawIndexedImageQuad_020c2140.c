#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct MenuImage {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

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

extern const MtxFx33 data_ov085_020c2314;
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

void DrawIndexedImageQuad_020c2140(const MenuImage *images, u32 indexColor, u32 pos, fx32 depth)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov085_020c2314;
    const MenuImage *image = &images[indexColor >> 16];

    scale.x = image->width << 12;
    scale.y = image->height << 12;
    scale.z = FX32_ONE;
    trans.x = (scale.x >> 1) + ((s16)(pos >> 16) << 12);
    trans.y = (192 << 12) - (((s16)pos << 12) + (scale.y >> 1));
    trans.z = depth;
    func_0201931c(&scale);
    func_020192ec(&trans);
    MI_Copy36B_01ff87c4(&rot, &G3D_BASE_ROT);
    G3D_FLAGS &= ~0xa4;
    FlushGeometryState_02019230();
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, image->texParams, 2);
    GeCommand1(0x29, 0x1f08c0);
    GeCommand1(0x20, (u16)indexColor);
    GeCommand1(0x40, 1);
    GeTexCoord(0, 0);
    GeVtx(-0x800, 0x800, 0);
    GeTexCoord(scale.x, 0);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(scale.x, scale.y);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(0, scale.y);
    GeVtx(-0x800, -0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
