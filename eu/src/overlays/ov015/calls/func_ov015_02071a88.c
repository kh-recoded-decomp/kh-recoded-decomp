#include "nitro/types.h"

extern void func_ov002_02062014(int mode);
extern void SetupPanelGraphics(void);
extern void DrawCenteredLabel(void);
extern void DrawPanelInfoText(void);
extern void func_ov015_02070af8(int mode);

void func_ov015_02071a88(void) {
    SetupPanelGraphics();
    DrawCenteredLabel();
    DrawPanelInfoText();
    func_ov002_02062014(1);
    func_ov015_02070af8(1);
}
