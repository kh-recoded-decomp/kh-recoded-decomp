#include "nitro/types.h"

extern int contextData_020c0060[];

BOOL IsContextFlag10Clear_020bb554(void)
{
    BOOL result = TRUE;
    if (*(u16 *)(contextData_020c0060[1] + 6) & 0x10) {
        result = FALSE;
    }
    return result;
}
