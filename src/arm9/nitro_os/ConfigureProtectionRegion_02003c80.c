#include "nitro/types.h"

extern void CallTableFunc_02003be4(int index, void *arg);

void ConfigureProtectionRegion_02003c80(int region, u32 base, u32 size, u32 flags)
{
    u32 shift = (size - 0x16) >> 1;
    u32 value = size | (base & (-0x1000 << shift)) | 1;
    CallTableFunc_02003be4(region, (void *)value);
}
