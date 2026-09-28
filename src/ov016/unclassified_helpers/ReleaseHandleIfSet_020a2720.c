#include "nitro/types.h"

extern void func_0202eee8(void);
extern void func_0202a1c4(s32 handle);

void ReleaseHandleIfSet_020a2720(s32 *handle)
{
    if (*handle != 0) {
        func_0202eee8();
        func_0202a1c4(*handle);
        *handle = 0;
    }
}
