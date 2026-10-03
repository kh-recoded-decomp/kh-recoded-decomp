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

extern const MtxFx33 data_ov075_020d1794;
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

void DrawMenuImageCentered_020d10e0(const MenuImage *images, u32 select, u32 pos, fx32 depth)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov075_020d1794;
    const MenuImage *image = &images[select >> 16];

    scale.x = image->width << 12;
    scale.y = image->height << 12;
    scale.z = FX32_ONE;
    trans.x = (scale.x >> 1) + ((s16)(pos >> 16) << 12);
    trans.y = (192 << 12) - (((s16)pos << 12) + (scale.y >> 1));
    trans.z = depth;
    func_0201931c(&scale);
    func_020192ec(&trans);
    MI_Copy36B_01ff87c4(&rot, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryState_02019230();
    QueueOrSendGeometryCommand_01ffa37c(0x2b2a, image->texParams, 2);
    GeCommand1(0x29, 0x1f08e0);
    GeCommand1(0x20, (u16)select);
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
