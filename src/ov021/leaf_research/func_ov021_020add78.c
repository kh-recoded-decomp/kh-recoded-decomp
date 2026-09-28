#include "nitro/types.h"

extern u32 func_ov001_0206db5c();
extern u32 func_ov052_020cef20();
extern u32 func_ov052_020d1170();
extern u32 func_ov052_020d1238();

s32 func_ov021_020add78(int self, s32 *event, u32 *errorCode)
{
    s32 handle;
    s32 result;

    handle = func_ov001_0206db5c(*(u32 *)(self + 0x14));
    *(u8 *)(handle + 0xa51) = 0;
    *errorCode = 0x16;
    if ((event[0x1a] != 1) || (result = func_ov052_020d1238(handle, errorCode), result == 0)) {
        if ((*event == 0x88) || (*event == 0x8d)) {
            func_ov052_020cef20(handle);
        }
        func_ov052_020d1170(handle, 0);
        if (event[1] == 4) {
            *errorCode = 0x18;
        }
        result = event[0xf];
    }
    return result;
}
