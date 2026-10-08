#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    s32 modeId;
} SoundCtx;

typedef struct {
    u8 pad_0000[0x28d5];
    u8 progressStage;
} SaveWork;

extern SoundCtx *data_ov033_020baae0;
extern SaveWork *data_0205fe0c;
extern u32 func_ov001_02063620(void);
extern void SetPanelEnabled(int mode);
extern void FadeBgmVolume(int targetVolume, int frames);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);
extern void SetGlobalPackedBit(int bitIndex);
extern void InitOverlayState(s32 modeId);

s32 BeginResumeMode(void)
{
    SoundCtx *ctx = data_ov033_020baae0;

    if (func_ov001_02063620() != 0) {
        return -1;
    }
    SetPanelEnabled(0);
    FadeBgmVolume(0x40, 10);
    if (ctx->modeId == 0x40000002) {
        data_0205fe0c->progressStage = 7;
        WriteGlobalPackedBits(0x3537, 0x20, 0x4800);
        WriteGlobalPackedBits(0x3557, 0x20, 0);
        WriteGlobalPackedBits(0x3577, 0x20, -0x5000);
        WriteGlobalPackedBits(0x3597, 0x10, 0);
        WriteGlobalPackedBits(0x330b, 10, 800);
        WriteGlobalPackedBits(0x3315, 10, 8);
        SetGlobalPackedBit(0xbea);
    }
    InitOverlayState(ctx->modeId);
    if (ctx->flags & 1) {
        ctx->flags &= ~1;
    }
    data_ov033_020baae0->flags |= 0x8000;
    return 1;
}
