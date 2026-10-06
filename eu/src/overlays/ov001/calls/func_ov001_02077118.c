#include "nitro/types.h"

BOOL func_ov001_02077118(s32 *actor)
{
    s32 kind;

    if (actor[4] == 3) {
        return TRUE;
    }
    kind = actor[0];
    if (kind == 0xa0) {
        return TRUE;
    }
    if (kind == 0xa2) {
        return TRUE;
    }
    if (kind == 0xa1) {
        return TRUE;
    }
    if (kind == 0xb1) {
        return TRUE;
    }
    return FALSE;
}
