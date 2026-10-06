#include "nitro/types.h"

extern int func_ov001_020645c8(u32 flag);

u32 func_ov001_0206e280(void)
{
    int flag;
    u32 result;

    result = 1;
    flag = func_ov001_020645c8(0x3609);
    if (((flag == 0) && (flag = func_ov001_020645c8(0x360a), flag == 0)) &&
        (flag = func_ov001_020645c8(0x360b), flag != 0)) {
        result = 0;
    }
    return result;
}
