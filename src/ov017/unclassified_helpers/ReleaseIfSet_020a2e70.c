#include "nitro/types.h"

extern void func_0202a1c4();

void ReleaseIfSet_020a2e70(void **ptr)
{
    if (*ptr != 0) {
        func_0202a1c4();
        *ptr = 0;
    }
}
