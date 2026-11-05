#include "nitro/types.h"

extern u8 *data_ov001_020a04e8;

void *GetPanelItemHighlightPalette(void)
{
    return data_ov001_020a04e8 + 0xf4;
}
