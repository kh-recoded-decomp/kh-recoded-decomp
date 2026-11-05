#include "nitro/types.h"

extern u8 *data_ov001_020a04f8;

u32 GetFieldObjectListHead(void)
{
    return *(const u32 *)(data_ov001_020a04f8 + 0x8);
}
