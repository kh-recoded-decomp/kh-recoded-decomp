#pragma opt_propagation off
#pragma opt_common_subs off
#include "src/overlays/ov015/WirelessMenuContext.h"

extern WirelessMenuContext *gWirelessMenuWork;
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_EndLoadOBJExtPltt(void);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);

void AnimateWirelessHighlightPalette(void)
{
    WirelessMenuContext *context;
    WirelessPaletteColor color, base;
    base = gWirelessMenuWork->baseColor;
    color = gWirelessMenuWork->highlightColor;
    u16 red = color.rgb.red;

    if (red == 0) {
        gWirelessMenuWork->paletteFlags.increasing = 1;
    } else if (red == base.rgb.red) {
        gWirelessMenuWork->paletteFlags.increasing = 0;
    }

    context = gWirelessMenuWork;
    if (context->paletteFlags.increasing) {
        color.rgb.red = red + 1;
        color.rgb.blue = red;
        color.rgb.green = color.rgb.blue;
    } else {
        color.rgb.red = red + (u16)-1;
        color.rgb.blue = red;
        color.rgb.green = color.rgb.blue;
    }
    context->highlightColor = color;

    if (gWirelessMenuWork->paletteFlags.subEngine) {
        GXS_BeginLoadOBJExtPltt();
        *(volatile u16 *)0x068a0002 = gWirelessMenuWork->highlightColor.value;
        GXS_EndLoadOBJExtPltt();
    } else {
        GX_BeginLoadOBJExtPltt();
        *(volatile u16 *)0x06890002 = gWirelessMenuWork->highlightColor.value;
        GX_EndLoadOBJExtPltt();
    }
}
