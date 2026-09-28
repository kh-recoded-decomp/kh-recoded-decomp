#include "nitro/types.h"

extern int func_ov001_0206db5c();

int func_ov001_0206dc4c(void)
{
    int slot;

    slot = func_ov001_0206db5c();
    if (slot != 0) {
        return slot + 0xbc;
    }
    return 0;
}
