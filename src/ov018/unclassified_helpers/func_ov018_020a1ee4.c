#include "nitro/types.h"

BOOL func_ov018_020a1ee4(int object)
{
    BOOL result = TRUE;

    if ((*(s32 *)(object + 0xa0) != 1) && (*(s32 *)(object + 0xa0) != 10)) {
        result = FALSE;
    }
    return result;
}
