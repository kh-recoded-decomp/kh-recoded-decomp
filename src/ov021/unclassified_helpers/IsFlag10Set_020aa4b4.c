#include "nitro/types.h"

BOOL IsFlag10Set_020aa4b4(int *flags)
{
    return (*flags & 0x10) > 0;
}
