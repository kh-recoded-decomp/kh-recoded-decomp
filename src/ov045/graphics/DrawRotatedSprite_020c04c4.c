#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct SpriteTexture {
    u8 unknown_00[0x04];
    u32 texParams[2];
} SpriteTexture;

extern const VecFx32 data_ov045_020c0768;
extern const VecFx32 data_ov045_020c075c;
extern const s16 data_0205356c[];
extern MtxFx33 data_0205a9b8;
extern GeometryState data_0205a9a4;
extern void MTX_RotZ33_01ff9258(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_0201931c(const VecFx32 *scale);
extern void func_020192ec(const VecFx32 *trans);
extern void MI_Copy36B_01ff87c4(const void *src, void *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);
extern void DrawTexturedQuad_020c03d0(fx32 left, fx32 top, fx32 right, fx32 bottom, fx16 x0, fx16 y0, fx16 x1, fx16 y1);

static inline void GeCommand1(u32 op, u32 param)
{
    QueueOrSendGeometryCommand_01ffa37c(op, &param, 1);
}

void DrawRotatedSprite_020c04c4(SpriteTexture *sprite, int size, int angle)
{
    VecFx32 trans = data_ov045_020c0768;
    VecFx32 scale = data_ov045_020c075c;
    MtxFx33 rot;
    int angleIndex;

    if (size != 0) {
        scale.x = scale.y = size << 7;
        angleIndex = (u16)angle >> 4;
        MTX_RotZ33_01ff9258(&rot, data_0205356c[angleIndex], data_0205356c[(0x400 - angleIndex) & 0xfff]);
        func_0201931c(&scale);
        MI_Copy36B_01ff87c4(&rot, &data_0205a9b8);
        data_0205a9a4.flags &= ~0xa4;
        func_020192ec(&trans);
        FlushGeometryState_02019230();
        QueueOrSendGeometryCommand_01ffa37c(0x2b2a, sprite->texParams, 2);
        GeCommand1(0x29, 0x1f08c0);
        GeCommand1(0x20, 0x7fff);
        DrawTexturedQuad_020c03d0(0, 0, 0x80000, 0x80000, -0x800, -0x800, 0x800, 0x800);
    }
}
