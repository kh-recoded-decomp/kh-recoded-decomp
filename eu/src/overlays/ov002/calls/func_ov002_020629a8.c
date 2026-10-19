#include "src/overlays/ov002/Ov002PanelState.h"

extern void func_ov002_02062b10(void);

void func_ov002_020629a8(void)
{
    ResetMainPanelGraphics();
    func_ov002_02062b10();
}
