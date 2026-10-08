#include "nitro/types.h"

extern u32 data_ov001_020a04f0;
extern u32 func_ov001_0207123c(void);
extern u32 GetSceneTagTracker(void);
extern void ClearTileTableRect(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void func_ov027_020b8288(u32 handle, u32 value);

void func_ov001_0207dfb4(void)
{
    u8 *context;
    u32 group;
    u32 handle;
    u32 value;

    context = (u8 *)data_ov001_020a04f0;
    group = func_ov001_0207123c();
    handle = GetSceneTagTracker();
    *(u32 *)(context + 8) = 0;
    ClearTileTableRect(group, 0xb, 0xe, 0, 4, 2);
    value = FindActiveRecordById(handle, 0x134);
    func_ov027_020b8288(handle, value);
    value = FindActiveRecordById(handle, 0x12e);
    func_ov027_020b8288(handle, value);
}
