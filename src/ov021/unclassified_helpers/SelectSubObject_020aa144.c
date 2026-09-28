#include "nitro/types.h"

void *SelectSubObject_020aa144(void *obj, s32 which)
{
    if (which != 0) {
        return (u8 *)obj + 0x18;
    }
    return (u8 *)obj + 8;
}
