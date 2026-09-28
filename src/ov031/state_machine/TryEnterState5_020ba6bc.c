#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void SetCachedSoundParams_0204dcec(u32 a, u32 b, u32 c);
extern u32 func_ov001_02067750(void);
extern void func_ov001_020677fc(void);
extern void func_ov001_0206781c(void);
extern void func_ov001_02067870(void);
extern u32 func_ov001_02067ed4(void);
extern u32 func_ov001_02068000(void);
extern u32 func_ov001_0206802c(void);
extern u32 func_ov001_020681c4(void);
extern u32 func_ov001_020681d4(void);
extern void func_ov001_020687b8(void);
extern void func_ov001_0207b0c0(u32 a, u32 b);
extern void func_ov001_0207eff0(void);
extern void func_ov001_020876cc(void);

u32 TryEnterState5_020ba6bc(void)
{
    u32 result;
    u32 a;
    u32 b;

    result = func_ov001_02067750();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_020876cc();
    func_ov001_020687b8();
    func_ov001_0206781c();
    func_ov001_020677fc();
    func_ov001_02067ed4();
    a = func_ov001_02068000();
    func_ov001_02067ed4();
    b = func_ov001_0206802c();
    SetCachedSoundParams_0204dcec(a, b, 0x7f);
    func_ov001_0207eff0();
    func_ov001_02067870();
    func_ov001_02067ed4();
    a = func_ov001_020681d4();
    b = func_ov001_020681c4();
    func_ov001_0207b0c0(b, a);
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 5;
}
