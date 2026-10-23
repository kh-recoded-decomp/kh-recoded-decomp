#include "nitro/types.h"

void MIi_CpuClear16(u16 value, void *destination, u32 size)
{
    u32 offset = 0;

clearNextHalfword:
    /* The primitive compares byte offsets and the size as signed values. */
    if ((s32)offset < (s32)size) {
        *(u16 *)((u8 *)destination + offset) = value;
        offset += sizeof(u16);
        goto clearNextHalfword;
    }
}
