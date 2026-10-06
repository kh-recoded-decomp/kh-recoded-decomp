#include "nitro/types.h"

extern s32 data_0205fde4;
extern s32 data_ov001_020a04bc;
extern s32 GXx_GetMasterBrightness_(u32 reg);
extern void SetBrightnessAndSyncMain(s32 callerId);
extern s32 func_02029f5c(void);
extern s32 func_ov001_02064490(void);

s32 func_ov001_0206e750(s32 callerId)
{
    s32 ctx;
    s32 ok;
    s32 check;

    ctx = data_ov001_020a04bc;
    if (data_ov001_020a04bc == 0) {
        return 0;
    }
    ok = *(s32 *)(ctx + 0xf4);
    if (ok == 0) {
        return 0;
    }
    check = GXx_GetMasterBrightness_(0x400006c);
    if (*(s8 *)(ctx + 0xf0) == check) {
        check = func_02029f5c();
        if (*(s8 *)(ctx + 0xf0) == check) goto stillOwned;
    }
    ok = 0;
stillOwned:
    check = func_ov001_02064490();
    if ((check != 0) || (data_0205fde4 != 0)) {
        ok = 0;
    }
    if (ok != 0) {
        SetBrightnessAndSyncMain(callerId);
        *(s8 *)(ctx + 0xf0) = (s8)callerId;
    }
    *(s32 *)(ctx + 0xf4) = ok;
    return ok;
}
