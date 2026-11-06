#include "nitro/types.h"

extern u8 *gFieldEntryPoolManager;

u32 GetFieldEntryListHead(void)
{
    return *(const u32 *)(gFieldEntryPoolManager + 0x8);
}
