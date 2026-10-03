#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct PanelSprite {
    u32 texParams[2];
    u8 unknown_08[0x1a];
    u8 alpha : 5;
    u8 depthOffset : 3;
} PanelSprite;

extern const VecFx32 data_ov045_020c0750;
extern const VecFx32 data_ov045_020c0744;
extern const MtxFx33 data_ov045_020c07bc;
extern MtxFx33 data_0205a9b8;
extern GeometryState data_0205a9a4;
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

void DrawLayeredPanel_020c05a0(PanelSprite *sprite, BOOL split)
{
    VecFx32 trans = data_ov045_020c0750;
    VecFx32 scale = data_ov045_020c0744;
    MtxFx33 rot = data_ov045_020c07bc;

    if (sprite->alpha != 0) {
        trans.z -= sprite->depthOffset;
        func_0201931c(&scale);
        MI_Copy36B_01ff87c4(&rot, &data_0205a9b8);
        data_0205a9a4.flags &= ~0xa4;
        func_020192ec(&trans);
        FlushGeometryState_02019230();
        QueueOrSendGeometryCommand_01ffa37c(0x2b2a, sprite->texParams, 2);
        GeCommand1(0x29, (sprite->alpha << 16) | 0x8c0);
        GeCommand1(0x20, 0x7fff);
        if (split) {
            DrawTexturedQuad_020c03d0(0, 0, 0, 0, -0x800, -0x800, 0x800, -0x5ff);
            DrawTexturedQuad_020c03d0(0, 0, 0, 0x40000, -0x800, -0x5ff, -0x200, -0xab);
            DrawTexturedQuad_020c03d0(0, 0, 0x40000, 0x40000, -0x200, -0x5ff, 0x200, -0xab);
            DrawTexturedQuad_020c03d0(0x40000, 0, 0x40000, 0x40000, 0x200, -0x5ff, 0x800, -0xab);
            DrawTexturedQuad_020c03d0(0x40000, 0x40000, 0x40000, 0x40000, -0x800, -0xab, 0x800, 0x800);
            return;
        }
        DrawTexturedQuad_020c03d0(0, 0, 0, 0, -0x800, -0x800, 0x800, 0x800);
    }
}
