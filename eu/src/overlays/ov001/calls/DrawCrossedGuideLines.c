#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalState {
    u8 pad_00[0x94];
    MtxFx33 baseRot;
    u8 pad_b8[0x1c];
    u32 flag;
} G3dGlobalState;

extern G3dGlobalState NNS_G3dGlb;
extern const VecFx32 data_ov001_0209e050;
extern const VecFx32 data_ov001_0209e05c;
extern const MtxFx33 data_ov001_0209e0c8;

extern void NNS_G3dGlbSetBaseScale(const VecFx32 *scale);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *trans);
extern void MI_Copy36B(const void *src, void *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    NNS_G3dGeBufferOP_N(op, &param, 1);
}

static inline void GePolygonAttr(int light, int polyMode, int cullMode, int polygonId, int alpha, int misc)
{
    u32 data = light | (polyMode << 4) | (cullMode << 6) | misc | (polygonId << 24) | (alpha << 16);
    NNS_G3dGeBufferOP_N(0x29, &data, 1);
}

static inline void GeVtx(fx16 x, fx16 y, fx16 z)
{
    u32 data[2];
    data[0] = (u16)x | ((u16)y << 16);
    data[1] = (u16)z;
    NNS_G3dGeBufferOP_N(0x23, data, 2);
}

void DrawCrossedGuideLines(void)
{
    VecFx32 trans = data_ov001_0209e050;
    VecFx32 scale = data_ov001_0209e05c;
    MtxFx33 rot = data_ov001_0209e0c8;

    NNS_G3dGlbSetBaseScale(&scale);
    NNS_G3dGlbSetBaseTrans(&trans);
    MI_Copy36B(&rot, &NNS_G3dGlb.baseRot);
    NNS_G3dGlb.flag &= ~0xa4;
    NNS_G3dGlbFlushWVP();

    GePolygonAttr(0, 0, 3, 0, 31, 0);
    GeCommand1(0x40, 1);
    GeCommand1(0x20, 0x3e0);
    GeVtx(0x69, 0xbf, 0x1fff);
    GeVtx(0x68, 0xbf, 0x1fff);
    GeVtx(0xba, 0, 0x1fff);
    GeVtx(0xbb, 0, 0x1fff);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
    GeCommand1(0x20, 0x3e0);
    GeVtx(0x99, 0xbf, 0x1fff);
    GeVtx(0x98, 0xbf, 0x1fff);
    GeVtx(0x46, 0, 0x1fff);
    GeVtx(0x47, 0, 0x1fff);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
