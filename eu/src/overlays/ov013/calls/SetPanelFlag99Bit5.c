#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x99];
    u8 actionFlags;
} PanelState;

extern PanelState *data_ov013_02074ce0;

void SetPanelFlag99Bit5(void)
{
    data_ov013_02074ce0->actionFlags |= 0x20;
}
