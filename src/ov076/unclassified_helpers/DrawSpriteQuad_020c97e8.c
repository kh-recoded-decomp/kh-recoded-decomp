#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct SpriteQuad {
    fx32 texLeft;
    fx32 texRight;
    fx32 texTop;
    fx32 texBottom;
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot;
    u16 color;
    const u32 *texParams;
} SpriteQuad;

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

void DrawSpriteQuad_020c97e8(const SpriteQuad *quad)
{
    func_0201931c(&quad->scale);
    func_020192ec(&quad->trans);
    MI_Copy36B_01ff87c4(&quad->rot, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryState_02019230();
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, quad->texParams, 2);
    GeCommand1(0x29, 0x1f08c0);
    GeCommand1(0x20, quad->color);
    GeCommand1(0x40, 1);
    GeTexCoord(quad->texLeft, quad->texTop);
    GeVtx(0, 0x1000, 0);
    GeTexCoord(quad->texRight, quad->texTop);
    GeVtx(0x1000, 0x1000, 0);
    GeTexCoord(quad->texRight, quad->texBottom);
    GeVtx(0x1000, 0, 0);
    GeTexCoord(quad->texLeft, quad->texBottom);
    GeVtx(0, 0, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
