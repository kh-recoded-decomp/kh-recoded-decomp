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

extern MoviePlayerCtx *gOv030SceneWork;
extern s8 GetCtxModeByte(void);
extern void LoadContextResourceGroups(int mode);
extern void ForwardSubModePairB(int a, int b);
extern void SetOverlayLayerVisible(int visible);
extern void ResumeTaskAndClearFlags(void);
extern void SetMenuHighlight(int highlight);
extern void SetFieldObjectInteractionsBlocked(int value);
extern BOOL IsSessionFlagSet(int flagId);
extern void SetFieldEntriesPaused(int paused);
extern void ReloadFirstType11FieldObjectModels(void);
extern VecFx32 *GetManagedActorPosition(int index);
extern SubModeView *GetActiveSubModeCameraWork(void);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern void CacheSeqArcStatus(int level);
extern void SetStreamVolumePercent(int percent);

int MoviePlayer_EnterPlayback(void)
{
    MoviePlayerCtx *ctx = gOv030SceneWork;
    int mode;

    if (GetCtxModeByte() == 1) {
        mode = 3;
    } else {
        mode = 0x23;
    }
    LoadContextResourceGroups(mode);
    ForwardSubModePairB(1, 0);
    SetOverlayLayerVisible(0);
    ResumeTaskAndClearFlags();
    SetMenuHighlight(1);
    SetFieldObjectInteractionsBlocked(0);
    if (!IsSessionFlagSet(0x3309) && ctx->pendingEntry != 3) {
        SetFieldEntriesPaused(0);
    }
    gOv030SceneWork->flags |= 0xc;
    if (ctx->pendingEntry == 0) {
        ctx->flags &= ~0x20;
    }
    ReloadFirstType11FieldObjectModels();
    gOv030SceneWork->cameraPos = *GetManagedActorPosition(0);
    gOv030SceneWork->cameraTarget = GetActiveSubModeCameraWork()->target;
    if (!IsSessionFlagSet(0x360c)) {
        UpdateEventObjects();
        ForwardToActiveService_02088074();
    }
    CacheSeqArcStatus(2);
    SetStreamVolumePercent(0x46);
    gOv030SceneWork->flags |= 0x8000;
    return 6;
}
