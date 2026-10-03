#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    int entryMode;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern char OverlayId13_0000000d[];
extern void func_ov013_0206c760(void);
extern void func_02029f98(int processor, int overlay_id);

void UnloadPanelOverlay13_02062e98(void)
{
    func_ov013_0206c760();
    func_02029f98(0, (int)OverlayId13_0000000d);
    g_panelState_0206c460->entryMode = 3;
}
