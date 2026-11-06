#include "nitro/types.h"

extern u32 gFieldObjectClassManager;
extern void SetPackedBit(void *bitfield, u32 bit);

void ObjectManager_SetFlagBit(u32 bit)
{
    SetPackedBit((void *)(gFieldObjectClassManager + 0x120), bit);
}
