#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalState {
    u8 pad_00[0x94];
    MtxFx33 baseRot;
    u8 pad_b8[0x1c];
    u32 flag;
} G3dGlobalState;

typedef struct SpriteQuad {
    u8 pad_00[0x04];
    s16 width;
    s16 height;
    u32 texParams[2];
    fx32 posX;
    fx32 posY;
    fx32 scaleX;
    fx32 scaleY;
    fx32 depth;
    u8 polygonId;
    u8 frame;
    u16 tiltAngle;
    u16 rollAngle;
    u8 alpha : 5;
} SpriteQuad;

typedef struct ScreenOffset {
    s16 x;
    s16 y;
} ScreenOffset;

extern G3dGlobalState data_0205a924;
extern const s16 data_0205356c[];

extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotZ33_01ff9258(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);

static inline void VecSet(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

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

void DrawSpriteFrameQuad_0206ab14(SpriteQuad *sprite, BOOL depthUpdate)
{
    ScreenOffset unusedOffset = {0, 0};
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot;
    MtxFx33 tilt;
    fx32 depth;
    int angleIndex;
    u32 frame;
    fx32 width;
    fx32 height;

    VecSet(&scale, sprite->width << 12, sprite->height << 12, FX32_ONE);
    scale.x = FixedPointMultiply12(sprite->scaleX, scale.x);
    scale.y = -FixedPointMultiply12(sprite->scaleY, scale.y);
    func_0201931c(&scale);

    depth = sprite->depth;
    if (depth > FX32_ONE) {
        depth = FX32_ONE;
    }
    VecSet(&trans, sprite->posX, 0xbf000 - sprite->posY, 0x400000 - depth);
    func_020192ec(&trans);

    angleIndex = (u16)(0x10000 - sprite->rollAngle) >> 4;
    MTX_RotZ33_01ff9258(&rot, data_0205356c[angleIndex], data_0205356c[(0x400 - angleIndex) & 0xfff]);
    if (sprite->tiltAngle != 0) {
        MTX_Identity33_01ff90ec(&tilt);
        angleIndex = sprite->tiltAngle >> 4;
        MTX_RotY33_01ff923c(&tilt, data_0205356c[angleIndex], data_0205356c[(0x400 - angleIndex) & 0xfff]);
        MTX_Concat33_01ff9270(&rot, &tilt, &rot);
    }
    MI_Copy36B_01ff87c4(&rot, &data_0205a924.baseRot);
    data_0205a924.flag &= ~0xa4;
    FlushGeometryState_02019230();

    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, sprite->texParams, 2);
    GePolygonAttr(0, 0, 3, sprite->polygonId, sprite->alpha, depthUpdate ? 0x800 : 0);
    GeCommand1(0x20, 0x7fff);

    frame = sprite->frame;
    width = sprite->width << 12;
    height = sprite->height << 12;
    GeCommand1(0x40, 1);
    GeTexCoord(width * frame, 0);
    GeVtx(-0x800, -0x800, 0);
    GeTexCoord(width * (frame + 1), 0);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(width * (frame + 1), height);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(width * frame, height);
    GeVtx(-0x800, 0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
