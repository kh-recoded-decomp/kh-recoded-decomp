#include "nitro/types.h"

typedef void (*ResetCallback)(void *self, s32 arg);

extern u32 data_ov028_020bb3a0;
extern s32 FX_Div(s32 numer, s32 denom);
extern void func_0204d994(void);
extern void BeginScreenFadeOut(s32 value);
extern void func_ov001_0206a8c8(void);
extern void *GetBoundedEntryField(s32 value);
extern void SetFieldEntriesPaused(s32 value);
extern void Camera_SetFlag18IfStandard(s32 value);

void func_ov028_020bb1b4(void)
{
    void *self;
    ResetCallback callback;

    FX_Div(0x10000, 0x40000);
    func_ov001_0206a8c8();
    BeginScreenFadeOut(2);
    SetFieldEntriesPaused(1);
    self = GetBoundedEntryField(0);
    callback = *(ResetCallback *)((u8 *)self + 0x200);
    if (callback != 0) {
        callback(self, 0);
    }
    Camera_SetFlag18IfStandard(1);
    func_0204d994();
    *(u16 *)(data_ov028_020bb3a0 + 6) = *(u16 *)(data_ov028_020bb3a0 + 6) | 0x40;
}
