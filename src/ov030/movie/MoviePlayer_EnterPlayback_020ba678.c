#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 pendingEntry;
    u8 pad_09[0x38 - 0x09];
    VecFx32 cameraPos;
    VecFx32 cameraTarget;
} MoviePlayerCtx;

typedef struct {
    u8 pad_00[0x14];
    VecFx32 target;
} SubModeView;

extern MoviePlayerCtx *g_moviePlayerCtx_020bd000;
extern s8 GetCtxModeByte_02068084(void);
extern void func_ov001_0207d120(int mode);
extern void ForwardSubModePairB_020af57c(int a, int b);
extern void SetOverlayLayerVisible_0207ef40(int visible);
extern void ResumeTaskAndClearFlags_02066780(void);
extern void SetMenuHighlight_0206c2f8(int highlight);
extern void func_ov001_02087628(int value);
extern BOOL func_ov001_020645c8(int flagId);
extern void SetFieldEntriesPaused_0206e444(int paused);
extern void func_ov001_02082860(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern SubModeView *func_ov021_020af5f4(void);
extern void UpdateEventObjects_0206daf8(void);
extern void func_ov001_0208804c(void);
extern void CacheSeqArcStatus_0204e00c(int level);
extern void SetStreamVolumePercent_0204e070(int percent);

int MoviePlayer_EnterPlayback_020ba678(void)
{
    MoviePlayerCtx *ctx = g_moviePlayerCtx_020bd000;
    int mode;

    if (GetCtxModeByte_02068084() == 1) {
        mode = 3;
    } else {
        mode = 0x23;
    }
    func_ov001_0207d120(mode);
    ForwardSubModePairB_020af57c(1, 0);
    SetOverlayLayerVisible_0207ef40(0);
    ResumeTaskAndClearFlags_02066780();
    SetMenuHighlight_0206c2f8(1);
    func_ov001_02087628(0);
    if (!func_ov001_020645c8(0x3309) && ctx->pendingEntry != 3) {
        SetFieldEntriesPaused_0206e444(0);
    }
    g_moviePlayerCtx_020bd000->flags |= 0xc;
    if (ctx->pendingEntry == 0) {
        ctx->flags &= ~0x20;
    }
    func_ov001_02082860();
    g_moviePlayerCtx_020bd000->cameraPos = *func_ov001_0206dc4c(0);
    g_moviePlayerCtx_020bd000->cameraTarget = func_ov021_020af5f4()->target;
    if (!func_ov001_020645c8(0x360c)) {
        UpdateEventObjects_0206daf8();
        func_ov001_0208804c();
    }
    CacheSeqArcStatus_0204e00c(2);
    SetStreamVolumePercent_0204e070(0x46);
    g_moviePlayerCtx_020bd000->flags |= 0x8000;
    return 6;
}
