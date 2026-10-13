#include "src/overlays/ov013/Ov013PanelState.h"

extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);

void PulsePanelPaletteColor(void)
{
    PanelColor color;
    PanelColor limit;
    u16 red;

    limit = data_ov013_02074ce0->baseColor;
    color = data_ov013_02074ce0->pulseColor;
    red = color.red;
    if (red == 0) {
        data_ov013_02074ce0->pulseIncreasing = 1;
    } else if (red == limit.red) {
        data_ov013_02074ce0->pulseIncreasing = 0;
    }
    if (data_ov013_02074ce0->pulseIncreasing) {
        red = color.red++;
    } else {
        red = color.red--;
    }
    color.blue = red;
    color.green = color.blue;
    data_ov013_02074ce0->pulseColor = color;

    GX_BeginLoadOBJExtPltt();
    *(vu16 *)0x06890002 = data_ov013_02074ce0->pulseColor.raw;
    GX_EndLoadOBJExtPltt();
}
