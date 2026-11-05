#include "nitro/types.h"

extern void SetOv002PanelModeDirtyFromLowBit(int mode);
extern void SetupPanelGraphics(void);
extern void DrawCenteredLabel(void);
extern void DrawPanelInfoText(void);
extern void func_ov015_02070af8(int mode);

void func_ov015_02071a88(void) {
    SetupPanelGraphics();
    DrawCenteredLabel();
    DrawPanelInfoText();
    SetOv002PanelModeDirtyFromLowBit(1);
    func_ov015_02070af8(1);
}
