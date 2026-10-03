#include "nitro/types.h"

typedef struct RankEntry {
    s32 rank;
    s32 score;
} RankEntry;

typedef struct RankCategory {
    RankEntry entries[4];
} RankCategory;

typedef struct Ov038Context {
    u8 pad_0000[0xd0a8];
    s32 fadeTimer;
    s32 page;
    s32 stats[10];
    RankCategory categories[9];
    s32 selections[9];
    s32 currentCategory;
    u32 playTime;
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void DrawOv038PercentDigits_020bb35c(s32 poolIndex, s32 firstRecord, s32 value);
extern void func_ov038_020bb4e0(s32 poolIndex, s32 firstRecord, u32 totalSeconds);
extern void SetOv038PoolRecordFlags_020bb32c(s32 poolIndex, s32 recordIndex, int value);
extern void func_ov038_020bb41c(s32 poolIndex, s32 firstRecord, s32 value);
extern void PrepareAndStartStream_0204dd4c(int stream, int mode);
extern void ResetOv038ExitState_020bb638(int state);

s32 ShowOv038ResultsFadeIn_020ba768(void)
{
    Ov038Context *ctx = g_ov038Context_020bd144;
    int brightness = ctx->fadeTimer - 0x10;

    SetBrightnessAndSyncMain_02029e7c(brightness);
    SetSecondaryBrightness_02029ed0(brightness);
    if (ctx->fadeTimer == 0) {
        DrawOv038PercentDigits_020bb35c(1, 0, ctx->stats[0]);
        DrawOv038PercentDigits_020bb35c(1, 4, ctx->stats[1]);
        DrawOv038PercentDigits_020bb35c(1, 8, ctx->stats[2]);
        DrawOv038PercentDigits_020bb35c(1, 0xc, ctx->stats[3]);
        DrawOv038PercentDigits_020bb35c(1, 0x10, ctx->stats[4]);
        DrawOv038PercentDigits_020bb35c(1, 0x1d, ctx->stats[5]);
        DrawOv038PercentDigits_020bb35c(1, 0x21, ctx->stats[6]);
        DrawOv038PercentDigits_020bb35c(1, 0x25, ctx->stats[7]);
        DrawOv038PercentDigits_020bb35c(1, 0x29, ctx->stats[8]);
        DrawOv038PercentDigits_020bb35c(1, 0x2d, ctx->stats[9]);
        func_ov038_020bb4e0(1, 0x14, ctx->playTime);
        SetOv038PoolRecordFlags_020bb32c(1, 0x31, ctx->categories[0].entries[ctx->selections[0]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x32, ctx->categories[1].entries[ctx->selections[1]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x33, ctx->categories[2].entries[ctx->selections[2]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x34, ctx->categories[ctx->currentCategory].entries[ctx->selections[ctx->currentCategory]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x35, ctx->categories[6].entries[ctx->selections[6]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x36, ctx->categories[7].entries[ctx->selections[7]].rank);
        SetOv038PoolRecordFlags_020bb32c(1, 0x37, ctx->categories[8].entries[ctx->selections[8]].rank);
        func_ov038_020bb41c(1, 0x39, ctx->categories[0].entries[ctx->selections[0]].score);
        func_ov038_020bb41c(1, 0x3f, ctx->categories[1].entries[ctx->selections[1]].score);
        func_ov038_020bb41c(1, 0x45, ctx->categories[2].entries[ctx->selections[2]].score);
        func_ov038_020bb41c(1, 0x4b, ctx->categories[ctx->currentCategory].entries[ctx->selections[ctx->currentCategory]].score);
        func_ov038_020bb41c(1, 0x51, ctx->categories[6].entries[ctx->selections[6]].score);
        func_ov038_020bb41c(1, 0x57, ctx->categories[7].entries[ctx->selections[7]].score);
        func_ov038_020bb41c(1, 0x5d, ctx->categories[8].entries[ctx->selections[8]].score);
        PrepareAndStartStream_0204dd4c(0, 2);
    }
    if (++ctx->fadeTimer > 0x10) {
        ResetOv038ExitState_020bb638(2);
    }
    return 0;
}
