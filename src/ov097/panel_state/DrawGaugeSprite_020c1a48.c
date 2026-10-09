#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GaugeSprite {
    u8 pad_00[4];
    s16 width;
    s16 height;
    u32 texParams[2];
    fx32 posX;
    fx32 posY;
    fx32 scaleX;
    fx32 scaleY;
    fx32 depth;
    u8 alpha;
    u8 frame;
    u8 polygonId : 5;
} GaugeSprite;

extern int FixedPointMultiply12_02006450(int left, int right);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
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

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline void GePolygonAttr(int light, int polyMode, int cullMode, int polygonId, int alpha, u32 misc)
{
    u32 attr = light | (polyMode << 4) | (cullMode << 6) | misc | (polygonId << 24) | (alpha << 16);
    QueueOrSendGeometryCommand_01ffa37c(0x29, &attr, 1);
}

void DrawGaugeSprite_020c1a48(GaugeSprite *sprite, BOOL translucent)
{
    int i;
    VecFx32 scale;
    VecFx32 trans;
    fx32 depth;
    float debugX;
    float debugY;
    int frame;
    fx32 width;
    int height;
    fx32 offset;
    fx32 columnLeft;
    fx32 columnRight;

    SetVec(&scale, sprite->width << 12, sprite->height << 12, 0x1000);
    scale.x = FixedPointMultiply12_02006450(sprite->scaleX, scale.x);
    scale.y = -FixedPointMultiply12_02006450(sprite->scaleY, scale.y);
    func_0201931c(&scale);
    debugX = (float)scale.x / 4096.0f;
    debugY = (float)scale.y / 4096.0f;
    depth = sprite->depth;
    if (depth > 0x1000) {
        depth = 0x1000;
    }
    trans.x = sprite->posX - 0xc000;
    trans.y = 0xbf000 - sprite->posY;
    trans.z = 0x400000 - depth;
    func_020192ec(&trans);
    FlushGeometryState_02019230();
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, sprite->texParams, 2);
    GePolygonAttr(0, 0, 3, sprite->alpha, sprite->polygonId, translucent ? 0x800 : 0);
    GeCommand1(0x20, 0x7fff);
    frame = sprite->frame;
    width = sprite->width << 12;
    height = sprite->height;
    GeCommand1(0x40, 1);
    GeTexCoord(width * frame, 0);
    GeVtx(-0x800, -0x800, 0);
    GeTexCoord(width * (frame + 1), 0);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(width * (frame + 1), height << 12);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(width * frame, height << 12);
    GeVtx(-0x800, 0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);

    trans.x += 0x4c000;
    trans.y += 0x40000;
    columnLeft = frame * 0x18000;
    columnRight = (frame + 1) * 0x18000;
    for (i = 0; i < 5; i++) {
        SetVec(&scale, 0x18000, -0x18000, 0x1000);
        func_0201931c(&scale);
        trans.y -= 0x18000;
        debugY = (float)trans.y / 4096.0f;
        func_020192ec(&trans);
        FlushGeometryState_02019230();
        QueueOrSendGeometryCommand_01ffa37c(0x2b2a, sprite->texParams, 2);
        GePolygonAttr(0, 0, 3, sprite->alpha, sprite->polygonId, translucent ? 0x800 : 0);
        GeCommand1(0x20, 0x7fff);
        offset = (i * 24) << 12;
        GeCommand1(0x40, 1);
        GeTexCoord(columnLeft + offset, 0x68000);
        GeVtx(-0x800, -0x800, 0);
        GeTexCoord(columnRight + offset, 0x68000);
        GeVtx(0x800, -0x800, 0);
        GeTexCoord(columnRight + offset, 0x80000);
        GeVtx(0x800, 0x800, 0);
        GeTexCoord(columnLeft + offset, 0x80000);
        GeVtx(-0x800, 0x800, 0);
        QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
    }
}





