#include "nitro/types.h"

BOOL IsAngleDifferenceLarge_020c4804(int from, int to)
{
    int diff = (u16)(to - from);

    if (diff <= 0x400 || 0x10000 - diff <= 0x400) {
        return FALSE;
    }
    return TRUE;
}
