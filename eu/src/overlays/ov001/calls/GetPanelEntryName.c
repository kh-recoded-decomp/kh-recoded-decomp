#include "nitro/types.h"

extern u32 gSubscenePanelWork;

u32 GetPanelEntryName(s32 index)
{
    return *(u32 *)(*(s32 *)(gSubscenePanelWork + 0x110) + index * 4);
}
