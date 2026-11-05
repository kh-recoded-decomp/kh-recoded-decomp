#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void SetPackedBit(void *bitfield, u32 bit);

void ObjectManager_SetFlagBit(u32 bit)
{
    SetPackedBit((void *)(data_ov001_020a04f8 + 0x120), bit);
}
