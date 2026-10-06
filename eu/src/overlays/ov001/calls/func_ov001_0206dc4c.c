#include "nitro/types.h"

extern int GetBoundedEntryField();

int func_ov001_0206dc4c(void)
{
    int slot;

    slot = GetBoundedEntryField();
    if (slot != 0) {
        return slot + 0xbc;
    }
    return 0;
}
