#include "src/overlays/ov013/Ov013PanelState.h"

extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);

void PulsePanelPaletteColor(void)
{
    PanelColor color;
    PanelColor limit;
    u16 red;

    limit = gOv013PanelGlobals->baseColor;
    color = gOv013PanelGlobals->pulseColor;
    red = color.red;
    if (red == 0) {
        gOv013PanelGlobals->pulseIncreasing = 1;
    } else if (red == limit.red) {
        gOv013PanelGlobals->pulseIncreasing = 0;
    }
    if (gOv013PanelGlobals->pulseIncreasing) {
        red = color.red++;
    } else {
        red = color.red--;
    }
    color.blue = red;
    color.green = color.blue;
    gOv013PanelGlobals->pulseColor = color;

    GX_BeginLoadOBJExtPltt();
    *(vu16 *)0x06890002 = gOv013PanelGlobals->pulseColor.raw;
    GX_EndLoadOBJExtPltt();
}
