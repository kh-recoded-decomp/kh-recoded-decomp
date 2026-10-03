#include "nitro/types.h"

extern u32 g_uiContext_020b7760;
extern u32 g_pendingTagData_020b773c;

extern void NotifyBothOrOne_02001154(u32 a, u32 b, int index);
extern void func_ov027_020b984c(u32 ctx, u32 enable);
extern void func_ov025_020b71d8(u32 list);
extern void DestroyObjectsAndRelease_020b8c58(u32 ctx);
extern void func_ov027_020b7dfc(u32 ctx);
extern void FreeAllocatedBuffers_020b9a60(u32 buffers);
extern BOOL DestroyFndObjectList_020014f0(u32 container);
extern u32 func_ov001_0207b200(u32 arg);

void ShutdownMenuScreen_020b5e8c(void)
{
    u32 ctx = g_uiContext_020b7760;

    NotifyBothOrOne_02001154(1, (u32)&g_pendingTagData_020b773c, -1);
    func_ov027_020b984c(ctx + 0x4c, 0);
    func_ov025_020b71d8(ctx + 0x64f4);
    DestroyObjectsAndRelease_020b8c58(ctx + 0x4c);
    func_ov027_020b7dfc(ctx);
    *(u32 *)(ctx + 0x64e4) = 0;
    FreeAllocatedBuffers_020b9a60(ctx + 0x64c8);
    DestroyFndObjectList_020014f0(ctx + 0x669c);
    DestroyFndObjectList_020014f0(ctx + 0x6668);
    DestroyFndObjectList_020014f0(ctx + 0x6634);
    func_ov001_0207b200(0);
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
}
