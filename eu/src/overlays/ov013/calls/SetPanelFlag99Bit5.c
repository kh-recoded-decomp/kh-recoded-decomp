#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x99];
    u8 actionFlags;
} PanelState;

extern PanelState *gOv013PanelGlobals;

void SetPanelFlag99Bit5(void)
{
    gOv013PanelGlobals->actionFlags |= 0x20;
}
