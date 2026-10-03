#include "nitro/types.h"

extern char OverlayId15_0000000f[];
extern void func_02029f78(int processor, int overlay_id);
extern void InitPanelState_0206c480(void);

void LoadPanelOverlay15_02062ee0(void)
{
    func_02029f78(0, (int)OverlayId15_0000000f);
    InitPanelState_0206c480();
}
