#include "nitro/types.h"

extern BOOL IsSessionFlagSet(int flag);

BOOL IsSessionFlag3701Set(void)
{
    return IsSessionFlagSet(0x3701);
}
