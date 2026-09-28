#include "nitro/types.h"

extern u32 g_ov029SoundCtx_020baba0;
extern void func_ov001_0206de40();
extern u32 func_ov001_0206dc4c();
extern u32 func_ov001_0206dc80();
extern void func_ov001_02063524();
extern u32 func_ov001_0206dc38();
extern void func_ov001_020685d4();
extern void func_ov001_020676c4();
extern void func_ov001_0207ef40();
extern void func_ov001_0207ef78();
extern void func_ov001_0207d658();
extern void func_020365f0();
extern void func_02036434();
extern void ReleaseSeqArcHeapLevel_0204e040();
extern void StoreToGlobalPtr4Field28_0202a778();

int DisableOv029Sound_020ba768(void)
{
    s32 index;
    s32 count;
    u32 volume;
    u32 pan;

    index = 0;
    count = func_ov001_0206dc38();
    if (0 < count) {
        do {
            func_ov001_0206de40(index);
            volume = func_ov001_0206dc4c(index);
            pan = func_ov001_0206dc80(index);
            func_ov001_02063524(index, volume, pan);
            index = index + 1;
            count = func_ov001_0206dc38();
        } while (index < count);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef40(1);
    func_ov001_0207ef78();
    *(u16 *)(g_ov029SoundCtx_020baba0 + 6) = *(u16 *)(g_ov029SoundCtx_020baba0 + 6) & 0xfff3;
    func_ov001_0207d658();
    func_020365f0();
    func_02036434();
    ReleaseSeqArcHeapLevel_0204e040(1);
    StoreToGlobalPtr4Field28_0202a778(1);
    *(u16 *)(g_ov029SoundCtx_020baba0 + 6) = *(u16 *)(g_ov029SoundCtx_020baba0 + 6) | 0x8000;
    return 7;
}
