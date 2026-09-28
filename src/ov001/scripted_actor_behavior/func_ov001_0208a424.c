#include "nitro/types.h"

BOOL func_ov001_0208a424(u8 *actor, int mode)
{
    if (mode == 0) {
        if (*(s32 *)(actor + 0x858) == 0) {
            return TRUE;
        }
        return FALSE;
    }
    if ((*(s16 *)(actor + 0xd4) == -1) && (*(s8 *)(actor + 0xdc) == 0)) {
        return TRUE;
    }
    return FALSE;
}
