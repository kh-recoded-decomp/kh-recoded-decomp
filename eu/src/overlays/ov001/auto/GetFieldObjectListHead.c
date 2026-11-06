#include "nitro/types.h"

extern u8 *gFieldObjectClassManager;

u32 GetFieldObjectListHead(void)
{
    return *(const u32 *)(gFieldObjectClassManager + 0x8);
}
