#include "nitro/types.h"

extern u32 GetBoundedEntryField();
extern u32 RefreshLockTarget();
extern u32 ActivateSlotModelGroup();
extern u32 SelectFallStateHandler();

s32 func_ov021_020add98(int self, s32 *event, u32 *errorCode)
{
    s32 handle;
    s32 result;

    handle = GetBoundedEntryField(*(u32 *)(self + 0x14));
    *(u8 *)(handle + 0xa51) = 0;
    *errorCode = 0x16;
    if ((event[0x1a] != 1) || (result = SelectFallStateHandler(handle, errorCode), result == 0)) {
        if ((*event == 0x88) || (*event == 0x8d)) {
            RefreshLockTarget(handle);
        }
        ActivateSlotModelGroup(handle, 0);
        if (event[1] == 4) {
            *errorCode = 0x18;
        }
        result = event[0xf];
    }
    return result;
}
