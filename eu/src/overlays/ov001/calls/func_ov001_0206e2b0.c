#include "nitro/types.h"

extern int IsSessionFlagSet(u32 flag);
extern int func_ov001_02064784(void);

BOOL func_ov001_0206e2b0(void)
{
    int value;

    value = func_ov001_02064784();
    if ((value == 7) && (value = IsSessionFlagSet(0x370d), value != 0)) {
        return 1;
    }
    return 0;
}
