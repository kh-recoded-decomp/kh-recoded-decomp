#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

typedef struct FadeState {
    u8 pad_0000[0x3f00];
    s32 colorIndex;
    s32 alpha;
} FadeState;

extern FadeState *data_ov001_020a04e0;
extern const VecFx32 data_ov001_0209e40c;
extern const VecFx32 data_ov001_0209e418;
extern const VecFx32 data_ov001_0209e424;
extern const VecFx32 data_ov001_0209e400;
extern const VecFx32 data_02053438;
extern const u16 data_ov001_0209e3f8[];
extern u8 data_0205a92c[];
extern GlobalStateTail data_0205a9a4;
extern VecFx32 data_0205ab3c;
extern VecFx32 data_0205ab48;
extern VecFx32 data_0205ab54;
extern u8 data_0205a970[];
extern MtxFx33 data_0205a9b8;

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
    data_0205a9a4.flags &= ~0x50;
}

static inline void SetLookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target)
{
    data_0205ab3c = *camPos;
    data_0205ab48 = *camUp;
    data_0205ab54 = *target;
    func_01ff9b70(camPos, camUp, target, data_0205a970);
    data_0205a9a4.flags &= ~0xe8;
}

static inline void SetBaseRotation(const MtxFx33 *rotation)
{
    func_01ff87c4(rotation, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
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

void DrawScreenFadeQuad_020885a4(void)
{
    FadeState *state = data_ov001_020a04e0;
    VecFx32 scale;
    VecFx32 translation;
    VecFx32 camPos;
    VecFx32 target;
    VecFx32 camUp;
    MtxFx33 rotation;

    if (state->colorIndex == -1 || state->alpha == 0) {
        return;
    }
    scale = data_ov001_0209e40c;
    translation = data_ov001_0209e418;
    camPos = data_ov001_0209e424;
    target = data_02053438;
    camUp = data_ov001_0209e400;
    SetOrthoProjection(0, 0xc0000, 0, 0x100000, 0, 0x3000, 0x400000);
    SetLookAt(&camPos, &camUp, &target);
    func_0201931c(&translation);
    func_020192ec(&scale);
    func_01ff90ec(&rotation);
    SetBaseRotation(&rotation);
    FlushGeometryState_02019230();
    SendCommand1(0x29, (state->alpha << 16) | 0x3c0000c0);
    SendCommand1(0x20, data_ov001_0209e3f8[state->colorIndex]);
    SendCommand1(0x40, 1);
    SendVertex16(-0x800, -0x800, 0);
    SendVertex16(0x800, -0x800, 0);
    SendVertex16(0x800, 0x800, 0);
    SendVertex16(-0x800, 0x800, 0);
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}
