#include "nitro/types.h"

BOOL IsKind6ObjectStateNonzero(int object)
{
    return *(s8 *)(object + 0x52) != 0;
}
