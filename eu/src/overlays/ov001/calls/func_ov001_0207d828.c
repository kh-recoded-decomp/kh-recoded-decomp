#include "nitro/types.h"

extern u32 GetSceneTagTracker(void);
extern void NNS_GfdRegisterNewVramTransferTask(u32 a, u32 b, u32 c, u32 d);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void func_ov027_020b8230(u32 handle, u32 value);
extern u32 func_0202a7b8(void);

void func_ov001_0207d828(u8 *context, u32 param)
{
    u32 handle;
    u32 value;

    handle = GetSceneTagTracker();
    NNS_GfdRegisterNewVramTransferTask(7, 0x5400, param, 0x300);
    value = FindActiveRecordById(handle, 0x134);
    func_ov027_020b8230(handle, value);
    *(u32 *)(context + 0x14) = func_0202a7b8();
}
