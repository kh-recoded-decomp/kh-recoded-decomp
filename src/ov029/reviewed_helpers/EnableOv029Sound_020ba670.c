#include "nitro/types.h"

extern u32 g_ov029SoundCtx_020baba0;
extern void func_ov001_0207d120();
extern u32 func_ov001_02063a6c();
extern void func_ov021_020af57c();
extern void func_ov001_0207ef40();
extern void func_ov001_0206c2f8();
extern u32 func_ov001_020645c8();
extern void func_ov001_0206e444();
extern void CacheSeqArcStatus_0204e00c();
extern void StoreToGlobalPtr4Field28_0202a778();

int EnableOv029Sound_020ba670(void)
{
    u16 flags;
    u32 ctx;
    u32 handle;
    u32 ready;

    ctx = g_ov029SoundCtx_020baba0;
    func_ov001_0207d120(1);
    handle = func_ov001_02063a6c();
    func_ov021_020af57c(handle, 0);
    func_ov001_0207ef40(0);
    func_ov001_0206c2f8(0);
    ready = func_ov001_020645c8(0x3309);
    if (ready == 0) {
        func_ov001_0206e444(0);
    }
    *(u16 *)(g_ov029SoundCtx_020baba0 + 6) = *(u16 *)(g_ov029SoundCtx_020baba0 + 6) | 0xc;
    flags = *(u16 *)(ctx + 6);
    if ((flags & 1) != 0) {
        *(u16 *)(ctx + 6) = flags & 0xfffe;
    }
    CacheSeqArcStatus_0204e00c(2);
    StoreToGlobalPtr4Field28_0202a778(0);
    return 5;
}
