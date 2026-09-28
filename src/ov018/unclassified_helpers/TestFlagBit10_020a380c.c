#include "nitro/types.h"

BOOL TestFlagBit10_020a380c(int object)
{
    if ((*(u16 *)(object + 0x50) & 0x400) != 0) {
        return TRUE;
    }
    return FALSE;
}
