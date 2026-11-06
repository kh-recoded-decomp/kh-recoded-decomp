#include "nitro/types.h"

extern u8 *gSubscenePanelWork;

void *GetPanelItemHighlightPalette(void)
{
    return gSubscenePanelWork + 0xf4;
}
