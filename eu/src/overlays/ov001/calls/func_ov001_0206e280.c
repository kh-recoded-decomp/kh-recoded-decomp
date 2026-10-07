#include "nitro/types.h"

extern int IsSessionFlagSet(u32 flag);

u32 func_ov001_0206e280(void)
{
    int flag;
    u32 result;

    result = 1;
    flag = IsSessionFlagSet(0x3609);
    if (((flag == 0) && (flag = IsSessionFlagSet(0x360a), flag == 0)) &&
        (flag = IsSessionFlagSet(0x360b), flag != 0)) {
        result = 0;
    }
    return result;
}
