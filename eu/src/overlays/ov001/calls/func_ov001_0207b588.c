#include "nitro/types.h"

extern u32 func_ov001_0207b3f4(void);
extern u32 func_ov001_0207b610(void);
extern u32 LookupChannelEntry(s32 index);

extern u32 data_ov001_020a04e8;

u32 func_ov001_0207b588(s32 index)
{
    u32 fault;
    u32 result;

    fault = func_ov001_0207b3f4();
    if ((fault == 2) && (fault = func_ov001_0207b610(), fault != 0)) {
        result = LookupChannelEntry(index);
        return result;
    }
    return *(u32 *)(data_ov001_020a04e8 + index * 4 + 0xe4);
}
