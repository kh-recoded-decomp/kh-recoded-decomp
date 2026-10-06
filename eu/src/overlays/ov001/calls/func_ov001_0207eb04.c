#include "nitro/types.h"

extern u32 data_ov001_020a04f4;
extern u32 GetSceneTagTracker(void);
extern void func_ov001_0207dfb4(void);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void func_ov027_020b8288(u32 handle, u32 value);

void func_ov001_0207eb04(void)
{
    u32 handle;
    u32 value;

    handle = GetSceneTagTracker();
    func_ov001_0207dfb4();
    value = FindActiveRecordById(handle, 0x12e);
    func_ov027_020b8288(handle, value);
    *(u32 *)(data_ov001_020a04f4 + 0x20) = 0;
}
