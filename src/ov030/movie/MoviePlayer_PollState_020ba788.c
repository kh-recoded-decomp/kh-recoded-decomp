#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 pendingEntry;
} MoviePlayerCtx;

extern MoviePlayerCtx *g_moviePlayerCtx_020bd000;
extern void SetFieldEntriesPaused_0206e444(int paused);
extern void PlaySoundChecked_0204d8d0(int channel, int soundId);
extern BOOL IsEntryFlag2Active_020642d0(int index);
extern void func_0204d7f4(int value);
extern BOOL func_ov001_0206e644(void);
extern void func_ov030_020baccc(void);

int MoviePlayer_PollState_020ba788(void)
{
    MoviePlayerCtx *ctx = g_moviePlayerCtx_020bd000;

    if (ctx->flags & 0x4000) {
        SetFieldEntriesPaused_0206e444(1);
        g_moviePlayerCtx_020bd000->flags |= 0x8000;
        return 14;
    }
    if (ctx->flags & 0x12) {
        return -1;
    }
    if (ctx->flags & 0x40) {
        PlaySoundChecked_0204d8d0(0, 0x4e);
        g_moviePlayerCtx_020bd000->flags |= 0x8000;
        return 13;
    }
    if (ctx->pendingEntry >= 0) {
        return 9;
    }
    if (IsEntryFlag2Active_020642d0(0)) {
        g_moviePlayerCtx_020bd000->flags |= 0x10;
        func_0204d7f4(0x20);
        return 11;
    }
    if (func_ov001_0206e644()) {
        SetFieldEntriesPaused_0206e444(1);
        return 8;
    }
    func_ov030_020baccc();
    return -1;
}
