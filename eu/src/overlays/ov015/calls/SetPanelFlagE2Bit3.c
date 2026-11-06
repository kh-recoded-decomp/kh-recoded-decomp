#include "nitro/types.h"

typedef struct LinkPanelState {
    u8 pad_00[0xe2];
    u8 subPanelFlags;
} LinkPanelState;

extern LinkPanelState *gWirelessMenuWork;

void SetPanelFlagE2Bit3(void)
{
    gWirelessMenuWork->subPanelFlags |= 8;
}
