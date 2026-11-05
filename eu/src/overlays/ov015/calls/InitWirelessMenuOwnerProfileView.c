#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe0];
    u8 lowBits : 3;
    u8 panelActive : 1;
    u8 highBits : 4;
    u8 pad_e1[3];
    u32 exitRequest;
} PanelState;

extern void InitPanelScreenGraphics(void);
extern void DrawWirelessOwnerProfileText(void);
extern PanelState *data_ov015_0207e960;

void InitWirelessMenuOwnerProfileView(void) {
    InitPanelScreenGraphics();
    DrawWirelessOwnerProfileText();
    data_ov015_0207e960->panelActive = 0;
    data_ov015_0207e960->exitRequest = 0;
}
