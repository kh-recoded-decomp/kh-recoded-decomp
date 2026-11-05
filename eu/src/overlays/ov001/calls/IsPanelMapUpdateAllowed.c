#include "nitro/types.h"

extern u32 GetLoadedSubsceneMode(void);

u32 IsPanelMapUpdateAllowed(s32 panel)
{
    s32 mode;
    u32 result;

    result = 0;
    mode = GetLoadedSubsceneMode();
    if ((mode == 0) &&
        (((mode = *(s32 *)(panel + 0x30), mode == 4 || (mode == 6)) || (mode == 3)))) {
        result = 1;
    }
    return result;
}
