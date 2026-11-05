#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern void DrawSelectedEntryInfo(s32 mode);

void RefreshOv014SelectedEntryInfo(void)
{
    DrawSelectedEntryInfo(0);
    *(u8 *)(data_ov014_0206f9a0 + 0xcf8c) = 0;
}
