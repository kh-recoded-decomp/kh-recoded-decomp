#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_0207b36c(void);
extern void func_ov001_020667b4(void);
extern void func_ov001_020828ac(void);
extern s32 func_ov001_0206dc38(void);
extern void func_ov001_0206de40(s32 index);
extern u32 func_ov001_0206dc4c(s32 index);
extern u32 func_ov001_0206dc80(s32 index);
extern void func_ov001_02063524(s32 index, u32 a, u32 b);
extern void func_ov001_020685d4(void);
extern void func_ov001_020676c4(void);
extern void func_ov001_0207ef40(u32 arg);
extern void func_ov001_0207ef78(void);
extern void func_ov001_0207d658(void);
extern void func_020365f0(void);
extern void func_02036434(void);
extern void ReleaseSeqArcHeapLevel_0204e040(u32 level);
extern void SetStreamVolumePercent_0204e070(u32 percent);
extern void StoreToGlobalPtr4Field28_0202a778(u32 value);

u32 MoviePlayer_Stop_020ba9d0(void)
{
    s32 ready;
    u32 valueA;
    u32 valueB;
    s32 index;

    if (((*(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0x10) == 0) &&
        (ready = func_ov001_0207b36c(), ready == 0)) {
        return 0xffffffff;
    }
    func_ov001_020667b4();
    func_ov001_020828ac();
    index = 0;
    ready = func_ov001_0206dc38();
    if (0 < ready) {
        do {
            func_ov001_0206de40(index);
            valueA = func_ov001_0206dc4c(index);
            valueB = func_ov001_0206dc80(index);
            func_ov001_02063524(index, valueA, valueB);
            index = index + 1;
            ready = func_ov001_0206dc38();
        } while (index < ready);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef40(1);
    func_ov001_0207ef78();
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0xfff3;
    func_ov001_0207d658();
    func_020365f0();
    func_02036434();
    ReleaseSeqArcHeapLevel_0204e040(1);
    SetStreamVolumePercent_0204e070(100);
    StoreToGlobalPtr4Field28_0202a778(1);
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x8000;
    return 0x12;
}
