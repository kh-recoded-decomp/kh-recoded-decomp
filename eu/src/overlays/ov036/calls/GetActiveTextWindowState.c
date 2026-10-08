#include "nitro/types.h"

extern void *gTextWindowResourceTable[];
extern u32 func_ov036_020c280c(void *entry);

u32 GetActiveTextWindowState(void)
{
    return func_ov036_020c280c((u8 *)gTextWindowResourceTable[0] + 0x64fc);
}
