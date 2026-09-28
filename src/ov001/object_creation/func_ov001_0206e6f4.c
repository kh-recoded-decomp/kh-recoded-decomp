#include "nitro/types.h"

typedef struct OverlayFactoryContext {
    u8 pad_000[0xf0];
    u8 ownerId;    /* +0xf0 */
    u8 pad_0f1[3];
    s32 busy;

} OverlayFactoryContext;

extern s32 data_0205fde4;
extern OverlayFactoryContext *data_ov001_020a049c;
extern s32 func_02006770(u32 reg);
extern void func_02029e7c(s32 callerId);
extern s32 func_02029f48(void);
extern s32 func_ov001_02064490(void);

s32 func_ov001_0206e6f4(s32 callerId)
{
    OverlayFactoryContext *ctx;
    s32 ok;
    s32 busy;

    ctx = data_ov001_020a049c;
    ok = 1;
    if (data_ov001_020a049c == 0) {
        return 0;
    }
    busy = func_02006770(0x400006c);
    if ((busy != 0) || (busy = func_02029f48(), busy != 0)) {
        ok = 0;
    }
    busy = func_ov001_02064490();
    if ((busy != 0) || (data_0205fde4 != 0)) {
        ok = 0;
    }
    if (ok != 0) {
        ctx->ownerId = (u8)callerId;
        func_02029e7c(callerId);
    }
    ctx->busy = ok;
    return ok;
}
