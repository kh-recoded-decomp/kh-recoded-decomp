#include "nitro/types.h"

extern int func_ov001_020645c8(u32 flag);
extern int func_ov001_02064784(void);

BOOL func_ov001_0206e31c(void)
{
    int value;

    value = func_ov001_02064784();
    if ((value == 6) && (value = func_ov001_020645c8(0x3715), value != 0)) {
        return 1;
    }
    return 0;
}
