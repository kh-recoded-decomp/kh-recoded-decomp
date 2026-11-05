#include "nitro/types.h"

BOOL IsKind6ObjectType1Or10(int object)
{
    BOOL result = TRUE;

    if ((*(s32 *)(object + 0xa0) != 1) && (*(s32 *)(object + 0xa0) != 10)) {
        result = FALSE;
    }
    return result;
}
