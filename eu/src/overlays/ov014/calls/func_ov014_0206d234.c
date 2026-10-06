#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern void DrawSelectedEntryInfo(s32 mode);

void func_ov014_0206d234(void)
{
    DrawSelectedEntryInfo(0);
    *(u8 *)(data_ov014_0206f9a0 + 0xcf8c) = 0;
}
