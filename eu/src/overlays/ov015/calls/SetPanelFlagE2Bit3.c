#include "nitro/types.h"

typedef struct LinkPanelState {
    u8 pad_00[0xe2];
    u8 subPanelFlags;
} LinkPanelState;

extern LinkPanelState *data_ov015_0207e960;

void SetPanelFlagE2Bit3(void)
{
    data_ov015_0207e960->subPanelFlags |= 8;
}
