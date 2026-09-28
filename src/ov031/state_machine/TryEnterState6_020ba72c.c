#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_020645c8(u32 id);
extern void func_ov001_02066780(void);
extern void func_ov001_0206daf8(void);
extern void func_ov001_0206e444(u32 a);
extern void func_ov001_0207d120(u32 a);
extern void func_ov001_0207ef40(u32 a);
extern void func_ov001_02082860(void);
extern void func_ov001_02087628(u32 a);
extern void func_ov001_0208804c(void);
extern void func_ov021_020af57c(u32 a, u32 b);
extern void CacheSeqArcStatus_0204e00c(u32 index);

u32 TryEnterState6_020ba72c(void)
{
    u32 result;
    OverlayState *ctx;

    ctx = g_activeState_020bc800;
    func_ov001_0207d120(7);
    func_ov021_020af57c(1, 0);
    func_ov001_0207ef40(0);
    func_ov001_02066780();
    func_ov001_02087628(0);
    result = func_ov001_020645c8(0x3309);
    if (result == 0 && ctx->mode != 3) {
        func_ov001_0206e444(0);
    }
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0xc;
    if (ctx->mode == 0) {
        ctx->flags = ctx->flags & 0xffdf;
    }
    func_ov001_02082860();
    result = func_ov001_020645c8(0x360c);
    if (result == 0) {
        func_ov001_0206daf8();
        func_ov001_0208804c();
    }
    CacheSeqArcStatus_0204e00c(2);
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 6;
}
