#include "nitro/types.h"

extern u8 *gFieldEntryPoolManager;

u32 GetFieldObjectInteractionBlockMask(void)
{
    return *(const u8 *)(gFieldEntryPoolManager + 0x5) & 0x20;
}
