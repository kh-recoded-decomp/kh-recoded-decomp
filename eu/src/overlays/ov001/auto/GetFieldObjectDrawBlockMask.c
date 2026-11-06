#include "nitro/types.h"

extern u8 *gFieldObjectClassManager;

u32 GetFieldObjectDrawBlockMask(void)
{
    return *(const u8 *)(gFieldObjectClassManager + 0x14) & 0x1;
}
