#include "nitro/types.h"

extern u32 g_uiContext_020b7760;
extern u32 g_pendingTagData_020b773c;

extern u32 func_ov001_020711ec(u32 id);
extern void func_ov027_020b7e24(u32 ctx, u32 id);
extern u32 func_ov027_020b8184(u32 ctx, u32 id);
extern void TagTracker_InvokeCallback_020b8210(int *tracker, int arg);
extern void func_ov025_020b582c(u32 ctx);
extern void func_0200110c(int kind, void *data, u32 handler, u32 duration);
extern void func_ov027_020b984c(u32 ctx, u32 enable);

u32 RefreshTagCallbacksAndSchedule_020b5e24(void) {
    u32 ctx = g_uiContext_020b7760;
    u32 sound = func_ov001_020711ec(0x6a);
    u32 tag;

    func_ov027_020b7e24(ctx, sound);
    tag = func_ov027_020b8184(ctx, 0);
    TagTracker_InvokeCallback_020b8210((int *)ctx, tag);
    tag = func_ov027_020b8184(ctx, 1);
    TagTracker_InvokeCallback_020b8210((int *)ctx, tag);
    func_ov025_020b582c(ctx);
    func_0200110c(1, &g_pendingTagData_020b773c, 0x020b5801, 0xffffffff);
    func_ov027_020b984c(ctx + 0x4c, 1);
    return 0x020b5f09;
}
