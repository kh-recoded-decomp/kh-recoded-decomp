#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalState {
    u8 pad_00[0x94];
    MtxFx33 baseRot;
    u8 pad_b8[0x1c];
    u32 flag;
} G3dGlobalState;

typedef struct TextureQuad {
    s16 width;
    s16 height;
    u32 texParams[2];
} TextureQuad;

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

extern G3dGlobalState data_0205a924;
extern const MtxFx33 data_ov001_0209dfa4;

extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    QueueOrSendGeometryCommand_01ffa37c(op, &param, 1);
}

static inline void GePolygonAttr(int light, int polyMode, int cullMode, int polygonId, int alpha, int misc)
{
    u32 data = light | (polyMode << 4) | (cullMode << 6) | misc | (polygonId << 24) | (alpha << 16);
    QueueOrSendGeometryCommand_01ffa37c(0x29, &data, 1);
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

void DrawScaledTextureQuad_0207ca04(const ScreenPos *pos, fx32 zoom, TextureQuad *quad, u32 color)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov001_0209dfa4;
    fx32 width = quad->width << 12;
    fx32 height = quad->height << 12;

    scale.x = FixedPointMultiply12(width, zoom);
    scale.y = -FixedPointMultiply12(height, zoom);
    scale.z = FX32_ONE;
    func_0201931c(&scale);
    trans.x = pos->x;
    trans.y = 0xbf800 - pos->y;
    trans.z = 0x400000;
    func_020192ec(&trans);
    MI_Copy36B_01ff87c4(&rot, &data_0205a924.baseRot);
    data_0205a924.flag &= ~0xa4;
    FlushGeometryState_02019230();

    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, quad->texParams, 2);
    GePolygonAttr(0, 0, 3, 0, 31, 0x800);
    GeCommand1(0x20, color);
    GeCommand1(0x40, 1);
    GeTexCoord(0, 0);
    GeVtx(-0x800, -0x800, 0);
    GeTexCoord(width, 0);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(width, height);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(0, height);
    GeVtx(-0x800, 0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
