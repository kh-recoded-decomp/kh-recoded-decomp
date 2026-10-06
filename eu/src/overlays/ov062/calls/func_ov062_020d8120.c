#include "nitro/types.h"

extern u32 GetBoundedEntryField();
extern void CameraPath_Start();
extern u32 ActivateSlotModelGroup();

s32 func_ov062_020d8120(int self, s32 *event, u32 *errorCode)
{
    s32 handle;

    handle = GetBoundedEntryField(*(u32 *)(self + 0x14));
    *(u8 *)(handle + 0xa51) = 0;
    CameraPath_Start(event[0x24]);
    ActivateSlotModelGroup(handle, 0);
    *errorCode = 0x18;
    return event[0xf];
}
