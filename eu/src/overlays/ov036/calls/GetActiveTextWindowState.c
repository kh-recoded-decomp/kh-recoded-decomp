#include "nitro/types.h"

extern void *gTextWindowResourceTable[];
extern u32 GetTextWindowState(void *entry);

u32 GetActiveTextWindowState(void)
{
    return GetTextWindowState((u8 *)gTextWindowResourceTable[0] + 0x64fc);
}
