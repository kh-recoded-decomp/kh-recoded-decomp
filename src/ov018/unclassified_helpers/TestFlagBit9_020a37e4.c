#include "nitro/types.h"

BOOL TestFlagBit9_020a37e4(int object)
{
    if ((*(u16 *)(object + 0x50) & 0x200) != 0) {
        return TRUE;
    }
    return FALSE;
}
