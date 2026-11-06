#include "nitro/types.h"

typedef struct LinkPanelState {
    u8 pad_00[0xe0];
    u8 resultFlags;
} LinkPanelState;

extern LinkPanelState *gWirelessMenuWork;

void ClearPanelFlagE0Bit3(void)
{
    gWirelessMenuWork->resultFlags &= ~8;
}
