#include "nitro/types.h"

u16 GetFieldAt0x2_020a7550(void *obj)
{
    return *(u16 *)((u8 *)obj + 2);
}
