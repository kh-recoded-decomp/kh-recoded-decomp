#include "nitro/types.h"

BOOL func_ov001_0209d08c(u32 id)
{
    if (id == 99) {
        return TRUE;
    }
    if (id < 0x46) {
        return FALSE;
    }
    if (id <= 0x61) {
        return TRUE;
    }
    return FALSE;
}
