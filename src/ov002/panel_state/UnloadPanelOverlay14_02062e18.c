#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    int entryMode;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern char OverlayId14_0000000e[];
extern void ShutdownPanelObjects_0206cea0(void);
extern void func_02029f98(int processor, int overlay_id);

void UnloadPanelOverlay14_02062e18(void)
{
    ShutdownPanelObjects_0206cea0();
    func_02029f98(0, (int)OverlayId14_0000000e);
    g_panelState_0206c460->entryMode = 2;
}
