#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct CameraState {
    u8 pad_000[0xd4];
    u32 flags;
} CameraState;

typedef struct PanelWork {
    u8 pad_0000[0x10cc];
    s32 fadeAlpha;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3920;
extern const VecFx32 data_ov036_020c3360;
extern const VecFx32 data_ov036_020c336c;
extern const VecFx32 data_ov036_020c3378;
extern const VecFx32 data_ov036_020c3384;
extern const VecFx32 data_02053438;
extern u8 data_0205a92c[];
extern CameraState data_0205a924;
extern VecFx32 data_0205ab3c;
extern VecFx32 data_0205ab48;
extern VecFx32 data_0205ab54;
extern u8 data_0205a970[];
extern MtxFx33 data_0205a9b8;

extern BOOL func_02028940(void);
extern void MTX_OrthoW_02005f10(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, void *mtx);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, void *mtx);
extern void func_0201931c(const VecFx32 *vec);
extern void func_020192ec(const VecFx32 *vec);
extern void func_01ff90ec(MtxFx33 *mtx);
extern void func_01ff87c4(const MtxFx33 *src, MtxFx33 *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(int command, const u32 *params, int count);

static inline void SetOrthoProjection(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW)
{
    MTX_OrthoW_02005f10(t, b, l, r, n, f, scaleW, data_0205a92c);
    data_0205a924.flags &= ~0x50;
}

static inline void SetLookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target)
{
    data_0205ab3c = *camPos;
    data_0205ab48 = *camUp;
    data_0205ab54 = *target;
    func_01ff9b70(camPos, camUp, target, data_0205a970);
    data_0205a924.flags &= ~0xe8;
}

static inline void SetBaseRotation(const MtxFx33 *rotation)
{
    func_01ff87c4(rotation, &data_0205a9b8);
    data_0205a924.flags &= ~0xa4;
}

static inline void SendCommand1(int command, u32 value)
{
    u32 param = value;
    QueueOrSendGeometryCommand_01ffa37c(command, &param, 1);
}

static inline void SendVertex16(fx16 x, fx16 y, fx16 z)
{
    u32 params[2];
    params[0] = (u16)x | ((u32)(u16)y << 16);
    params[1] = (u16)z;
    QueueOrSendGeometryCommand_01ffa37c(0x23, params, 2);
}

void DrawPanelFadeQuad_020bad3c(void)
{
    PanelWork *work;
    VecFx32 scale;
    VecFx32 translation;
    VecFx32 camPos;
    VecFx32 target;
    VecFx32 camUp;
    MtxFx33 rotation;
    s32 alpha;
    PanelContext *context;
    const VecFx32 *zero;

    scale = data_ov036_020c3360;
    translation = data_ov036_020c336c;
    camPos = data_ov036_020c3378;
    zero = &data_02053438;
    target = *zero;
    context = &data_ov036_020c3920;
    work = context->work;
    camUp = data_ov036_020c3384;
    if (func_02028940()) {
        scale.z += 0x333;
    }
    SetOrthoProjection(0, 0xc0000, 0, 0x100000, 0, 0x3000, 0x400000);
    SetLookAt(&camPos, &camUp, &target);
    func_0201931c(&translation);
    func_020192ec(&scale);
    func_01ff90ec(&rotation);
    SetBaseRotation(&rotation);
    FlushGeometryState_02019230();
    if (func_02028940()) {
        alpha = 0xf;
    } else {
        alpha = work->fadeAlpha;
    }
    SendCommand1(0x29, (alpha << 16) | 0x3c0000c0);
    SendCommand1(0x20, 0);
    SendCommand1(0x40, 1);
    SendVertex16(-0x800, -0x800, 0);
    SendVertex16(0x800, -0x800, 0);
    SendVertex16(0x800, 0x800, 0);
    SendVertex16(-0x800, 0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
