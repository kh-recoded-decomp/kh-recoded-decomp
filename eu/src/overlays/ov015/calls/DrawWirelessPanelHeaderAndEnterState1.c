#include "nitro/types.h"

extern void SetOv002PanelModeDirtyFromLowBit(int mode);
extern void SetupPanelGraphics(void);
extern void DrawCenteredLabel(void);
extern void DrawPanelInfoText(void);
extern void SetWirelessMenuState(int mode);

void DrawWirelessPanelHeaderAndEnterState1(void) {
    SetupPanelGraphics();
    DrawCenteredLabel();
    DrawPanelInfoText();
    SetOv002PanelModeDirtyFromLowBit(1);
    SetWirelessMenuState(1);
}
