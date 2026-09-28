#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern void SetCachedSoundParams_0204dcec(u32 param1, u32 param2, u16 param3);
extern s32 func_ov001_02067750(void);
extern void func_ov001_020677fc(void);
extern void func_ov001_0206781c(void);
extern void func_ov001_02067870(void);
extern u32 func_ov001_02067ed4(void);
extern u32 func_ov001_02068000(void);
extern u32 func_ov001_0206802c(void);
extern u32 func_ov001_020681c4(void);
extern u32 func_ov001_020681d4(void);
extern void func_ov001_020687b8(s32 value);
extern void func_ov001_0207b0c0(u32 param1, u32 param2);
extern void InvokeListNodeCallbacks_0207eff0(void);

u32 func_ov028_020ba758(void)
{
    s32 value = func_ov001_02067750();
    u32 arg1;
    u32 arg2;

    if (value != 0) {
        func_ov001_020687b8(value);
        func_ov001_0206781c();
        func_ov001_020677fc();
        func_ov001_02067ed4();
        arg1 = func_ov001_02068000();
        func_ov001_02067ed4();
        arg2 = func_ov001_0206802c();
        SetCachedSoundParams_0204dcec(arg1, arg2, 0x7f);
        InvokeListNodeCallbacks_0207eff0();
        func_ov001_02067870();
        func_ov001_02067ed4();
        arg1 = func_ov001_020681d4();
        arg2 = func_ov001_020681c4();
        func_ov001_0207b0c0(arg2, arg1);
        *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 0x8000;
        return 5;
    }
    return 0xffffffff;
}
