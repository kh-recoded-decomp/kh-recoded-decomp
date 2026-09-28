#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_02067750(void);
extern void func_ov001_020687b8(void);
extern void func_ov001_0206781c(void);
extern void func_ov001_020677fc(void);
extern void func_ov001_02067ed4(void);
extern u32 func_ov001_02068000(void);
extern u32 func_ov001_0206802c(void);
extern void SetCachedSoundParams_0204dcec(u32 a, u32 b, u32 c);
extern void InvokeListNodeCallbacks_0207eff0(void);
extern void SetSlotConfigFlag38_02067870(void);
extern u32 func_ov001_020681d4(void);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 a, u32 b);

u32 func_ov030_020ba60c(void)
{
    s32 ready;
    u32 valueA;
    u32 valueB;

    ready = func_ov001_02067750();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_020687b8();
    func_ov001_0206781c();
    func_ov001_020677fc();
    func_ov001_02067ed4();
    valueA = func_ov001_02068000();
    func_ov001_02067ed4();
    valueB = func_ov001_0206802c();
    SetCachedSoundParams_0204dcec(valueA, valueB, 0x7f);
    InvokeListNodeCallbacks_0207eff0();
    SetSlotConfigFlag38_02067870();
    func_ov001_02067ed4();
    valueA = func_ov001_020681d4();
    valueB = func_ov001_020681c4();
    func_ov001_0207b0c0(valueB, valueA);
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x8000;
    return 5;
}
