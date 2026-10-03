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

typedef struct ImageQuad {
    const MenuImage *image;
    s16 x;
    s16 y;
    fx32 depth;
    u16 texOffsetS;
    u16 texOffsetT;
    u16 width;
    u16 height;
    u16 color;
} ImageQuad;

extern const MtxFx33 data_ov076_020cd144;
extern MtxFx33 data_0205a9b8;
extern GeometryState data_0205a9a4;
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

void DrawImageQuad_020c9a58(const ImageQuad *quad, BOOL decal)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov076_020cd144;
    fx32 texS;
    fx32 texT;
    int polyMode;

    scale.x = quad->width << 12;
    scale.y = quad->height << 12;
    scale.z = FX32_ONE;
    trans.x = (quad->x << 12) + (quad->width << 11);
    trans.y = (192 << 12) - ((quad->y << 12) + (quad->height << 11));
    trans.z = quad->depth;
    if (quad->y <= 0) {
        scale.y += FX32_ONE;
    }
    func_0201931c(&scale);
    func_020192ec(&trans);
    MI_Copy36B_01ff87c4(&rot, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryState_02019230();
    texS = quad->texOffsetS << 12;
    texT = quad->texOffsetT << 12;
    scale.x += texS;
    scale.y += texT;
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, quad->image->texParams, 2);
    polyMode = 2;
    if (!decal) {
        polyMode = 0;
    }
    GeCommand1(0x29, (polyMode << 4) | 0x1f08c0);
    GeCommand1(0x20, quad->color);
    GeCommand1(0x40, 1);
    GeTexCoord(texS, texT);
    GeVtx(-0x800, 0x800, 0);
    GeTexCoord(scale.x, texT);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(scale.x, scale.y);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(texS, scale.y);
    GeVtx(-0x800, -0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
