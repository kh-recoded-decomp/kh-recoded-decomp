#include "nitro/types.h"

extern char OverlayId13_0000000d[];
extern void func_02029f78(int processor, int overlay_id);
extern void InitPanelState_0206c480(void);

void LoadPanelOverlay13_02062e48(void)
{
    func_02029f78(0, (int)OverlayId13_0000000d);
    InitPanelState_0206c480();
}
