#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    u8 slotCTriggered : 1;
    u8 slotDTriggered : 1;
    u8 busy : 1;
    u8 unk_11_3 : 5;
} PanelState;

extern PanelState *g_panelState_0206c460;

u32 IsPanelBusy_02062c6c(void)
{
    return g_panelState_0206c460->busy;
}
