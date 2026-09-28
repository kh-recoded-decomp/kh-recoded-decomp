#include "nitro/types.h"

u16 GetFieldAt0xe_020a7558(void *obj)
{
    return *(u16 *)((u8 *)obj + 0xe);
}
