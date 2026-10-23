#include "nitro/types.h"

void MIi_CpuCopy16(const void *source, void *destination, u32 size)
{
    u32 offset = 0;

copyNextHalfword:
    /* The primitive compares byte offsets and the size as signed values. */
    if ((s32)offset < (s32)size) {
        *(u16 *)((u8 *)destination + offset) = *(const u16 *)((const u8 *)source + offset);
        offset += sizeof(u16);
        goto copyNextHalfword;
    }
}
