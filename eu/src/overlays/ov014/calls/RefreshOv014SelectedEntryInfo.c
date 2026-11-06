#include "nitro/types.h"

extern u32 gOv014PanelGlobals;
extern void DrawSelectedEntryInfo(s32 mode);

void RefreshOv014SelectedEntryInfo(void)
{
    DrawSelectedEntryInfo(0);
    *(u8 *)(gOv014PanelGlobals + 0xcf8c) = 0;
}
