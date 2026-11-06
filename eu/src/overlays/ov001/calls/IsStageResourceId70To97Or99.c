#include "nitro/types.h"

BOOL IsStageResourceId70To97Or99(u32 id)
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
