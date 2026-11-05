#include "nitro/types.h"

BOOL IsKind6ObjectState1Or2(int object)
{
    BOOL result = TRUE;

    if ((*(s8 *)(object + 0x52) != 1) && (*(s8 *)(object + 0x52) != 2)) {
        result = FALSE;
    }
    return result;
}
