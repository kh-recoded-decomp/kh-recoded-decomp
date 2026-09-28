#include "nitro/types.h"

extern u32 data_ov001_020a04d8;
extern void SetPackedBit(void *bitfield, u32 bit);

void func_ov001_0207f050(u32 bit)
{
    SetPackedBit((void *)(data_ov001_020a04d8 + 0x120), bit);
}
