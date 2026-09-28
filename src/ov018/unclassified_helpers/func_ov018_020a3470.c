#include "nitro/types.h"

BOOL func_ov018_020a3470(int object)
{
    BOOL result = TRUE;

    if ((*(s8 *)(object + 0x52) != 1) && (*(s8 *)(object + 0x52) != 2)) {
        result = FALSE;
    }
    return result;
}
