#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    int entryMode;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern char OverlayId15_0000000f[];
extern void ShutdownPanelState_0206c4d4(void);
extern void func_02029f98(int processor, int overlay_id);

void UnloadPanelOverlay15_02062f30(void)
{
    ShutdownPanelState_0206c4d4();
    func_02029f98(0, (int)OverlayId15_0000000f);
    g_panelState_0206c460->entryMode = 6;
}
