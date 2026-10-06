#include "nitro/types.h"

extern u32 data_ov001_020a04f0;
extern u32 GetSceneTagTracker(void);
extern u32 func_0202a7b8(void);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void func_ov027_020b8230(u32 handle, u32 value);
extern void ShowTwoDigitCounters(void *context);

void func_ov001_0207df6c(u32 param, u8 flag)
{
    u8 *context;
    u32 handle;
    u32 value;

    context = (u8 *)data_ov001_020a04f0;
    handle = GetSceneTagTracker();
    context[0] = 0;
    context[1] = flag;
    value = func_0202a7b8();
    *(u32 *)(context + 0x10) = value;
    *(u32 *)(context + 0x18) = 0;
    *(u32 *)(context + 0x1c) = param;
    value = FindActiveRecordById(handle, 0x12e);
    func_ov027_020b8230(handle, value);
    ShowTwoDigitCounters(context);
    *(u32 *)(context + 8) = 1;
}
