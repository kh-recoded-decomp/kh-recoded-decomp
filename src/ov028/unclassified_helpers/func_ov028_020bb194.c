#include "nitro/types.h"

typedef void (*ResetCallback)(void *self, s32 arg);

extern u32 g_fieldContext_020bb380;
extern s32 FX_Div_01ff9c84(s32 numer, s32 denom);
extern void func_0204d980(void);
extern void func_ov001_0206a7c0(s32 value);
extern void func_ov001_0206a8c8(void);
extern void *func_ov001_0206db5c(s32 value);
extern void func_ov001_0206e444(s32 value);
extern void func_ov046_020c1724(s32 value);

void func_ov028_020bb194(void)
{
    void *self;
    ResetCallback callback;

    FX_Div_01ff9c84(0x10000, 0x40000);
    func_ov001_0206a8c8();
    func_ov001_0206a7c0(2);
    func_ov001_0206e444(1);
    self = func_ov001_0206db5c(0);
    callback = *(ResetCallback *)((u8 *)self + 0x200);
    if (callback != 0) {
        callback(self, 0);
    }
    func_ov046_020c1724(1);
    func_0204d980();
    *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 0x40;
}
