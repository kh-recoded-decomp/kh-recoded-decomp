#include "nitro/types.h"

typedef struct LinkPanelState {
    u8 pad_00[0xe0];
    u8 resultFlags;
} LinkPanelState;

extern LinkPanelState *data_ov015_0207e960;

void ClearPanelFlagE0Bit3(void)
{
    data_ov015_0207e960->resultFlags &= ~8;
}
