#include "nitro/types.h"

extern u32 func_ov001_0207b3cc(void);
extern u32 func_ov001_0207b5e8(void);
extern u32 func_ov025_020b6270(s32 index);

extern u32 g_activePanel_020a04c8;

u32 func_ov001_0207b560(s32 index)
{
    u32 fault;
    u32 result;

    fault = func_ov001_0207b3cc();
    if ((fault == 2) && (fault = func_ov001_0207b5e8(), fault != 0)) {
        result = func_ov025_020b6270(index);
        return result;
    }
    return *(u32 *)(g_activePanel_020a04c8 + index * 4 + 0xe4);
}
