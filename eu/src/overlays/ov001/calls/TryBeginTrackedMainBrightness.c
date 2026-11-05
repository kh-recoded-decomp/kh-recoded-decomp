#include "nitro/types.h"

typedef struct OverlayFactoryContext {
    u8 pad_000[0xf0];
    u8 ownerId;    /* +0xf0 */
    u8 pad_0f1[3];
    s32 busy;

} OverlayFactoryContext;

extern s32 gPanelActive;
extern OverlayFactoryContext *data_ov001_020a04bc;
extern s32 GXx_GetMasterBrightness_(u32 reg);
extern void SetBrightnessAndSyncMain(s32 callerId);
extern s32 GetMainBrightnessSetting(void);
extern s32 InvokeSessionCheckCallbackOrDefault(void);

s32 TryBeginTrackedMainBrightness(s32 callerId)
{
    OverlayFactoryContext *ctx;
    s32 ok;
    s32 busy;

    ctx = data_ov001_020a04bc;
    ok = 1;
    if (data_ov001_020a04bc == 0) {
        return 0;
    }
    busy = GXx_GetMasterBrightness_(0x400006c);
    if ((busy != 0) || (busy = GetMainBrightnessSetting(), busy != 0)) {
        ok = 0;
    }
    busy = InvokeSessionCheckCallbackOrDefault();
    if ((busy != 0) || (gPanelActive != 0)) {
        ok = 0;
    }
    if (ok != 0) {
        ctx->ownerId = (u8)callerId;
        SetBrightnessAndSyncMain(callerId);
    }
    ctx->busy = ok;
    return ok;
}
