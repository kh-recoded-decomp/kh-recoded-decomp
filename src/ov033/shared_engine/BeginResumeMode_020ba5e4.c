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

extern SoundCtx *g_ov038SoundCtx_020baac0;
extern SaveWork *data_0205fe0c;
extern u32 func_ov001_02063620(void);
extern void func_02025438(int mode);
extern void FadeBgmVolume_0204d9a8(int targetVolume, int frames);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_ov039_020bb888(s32 modeId);

s32 BeginResumeMode_020ba5e4(void)
{
    SoundCtx *ctx = g_ov038SoundCtx_020baac0;

    if (func_ov001_02063620() != 0) {
        return -1;
    }
    func_02025438(0);
    FadeBgmVolume_0204d9a8(0x40, 10);
    if (ctx->modeId == 0x40000002) {
        data_0205fe0c->progressStage = 7;
        WriteGlobalPackedBits_02027360(0x3537, 0x20, 0x4800);
        WriteGlobalPackedBits_02027360(0x3557, 0x20, 0);
        WriteGlobalPackedBits_02027360(0x3577, 0x20, -0x5000);
        WriteGlobalPackedBits_02027360(0x3597, 0x10, 0);
        WriteGlobalPackedBits_02027360(0x330b, 10, 800);
        WriteGlobalPackedBits_02027360(0x3315, 10, 8);
        SetGlobalPackedBit_02027320(0xbea);
    }
    func_ov039_020bb888(ctx->modeId);
    if (ctx->flags & 1) {
        ctx->flags &= ~1;
    }
    g_ov038SoundCtx_020baac0->flags |= 0x8000;
    return 1;
}
