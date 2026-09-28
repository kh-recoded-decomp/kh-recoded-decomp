#include "nitro/types.h"

s32 GetFieldAt0x12_020a7560(void *obj)
{
    return *(s16 *)((u8 *)obj + 0x12);
}
