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

extern MoviePlayerCtx *data_ov030_020bd020;
extern s8 func_ov001_02068084(void);
extern void LoadContextResourceGroups(int mode);
extern void ForwardSubModePairB(int a, int b);
extern void SetOverlayLayerVisible(int visible);
extern void ResumeTaskAndClearFlags(void);
extern void SetMenuHighlight(int highlight);
extern void func_ov001_02087650(int value);
extern BOOL IsSessionFlagSet(int flagId);
extern void SetFieldEntriesPaused(int paused);
extern void func_ov001_02082888(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern SubModeView *func_ov021_020af614(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void CacheSeqArcStatus(int level);
extern void SetStreamVolumePercent(int percent);

int MoviePlayer_EnterPlayback(void)
{
    MoviePlayerCtx *ctx = data_ov030_020bd020;
    int mode;

    if (func_ov001_02068084() == 1) {
        mode = 3;
    } else {
        mode = 0x23;
    }
    LoadContextResourceGroups(mode);
    ForwardSubModePairB(1, 0);
    SetOverlayLayerVisible(0);
    ResumeTaskAndClearFlags();
    SetMenuHighlight(1);
    func_ov001_02087650(0);
    if (!IsSessionFlagSet(0x3309) && ctx->pendingEntry != 3) {
        SetFieldEntriesPaused(0);
    }
    data_ov030_020bd020->flags |= 0xc;
    if (ctx->pendingEntry == 0) {
        ctx->flags &= ~0x20;
    }
    func_ov001_02082888();
    data_ov030_020bd020->cameraPos = *func_ov001_0206dc4c(0);
    data_ov030_020bd020->cameraTarget = func_ov021_020af614()->target;
    if (!IsSessionFlagSet(0x360c)) {
        UpdateEventObjects();
        ForwardToActiveService_02088074();
    }
    CacheSeqArcStatus(2);
    SetStreamVolumePercent(0x46);
    data_ov030_020bd020->flags |= 0x8000;
    return 6;
}
