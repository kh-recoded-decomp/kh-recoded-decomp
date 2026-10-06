#include "nitro/types.h"

extern int GetBoundedEntryField(int index);

BOOL func_ov001_0206bc0c(void)
{
    int result;

    result = GetBoundedEntryField(0);
    return result == 0;
}
