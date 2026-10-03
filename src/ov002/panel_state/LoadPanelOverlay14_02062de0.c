#include "nitro/types.h"

extern char OverlayId14_0000000e[];
extern void func_02029f78(int processor, int overlay_id);
extern void InitPanelState_0206c480(void);

void LoadPanelOverlay14_02062de0(void)
{
    func_02029f78(0, (int)OverlayId14_0000000e);
    InitPanelState_0206c480();
}
