#pragma opt_propagation off
#pragma opt_common_subs off
#include "src/overlays/ov015/WirelessMenuContext.h"

extern WirelessMenuContext *data_ov015_0207e960;
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_EndLoadOBJExtPltt(void);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);

void AnimateWirelessHighlightPalette(void)
{
    WirelessMenuContext *context;
    WirelessPaletteColor color, base;
    base = data_ov015_0207e960->baseColor;
    color = data_ov015_0207e960->highlightColor;
    u16 red = color.rgb.red;

    if (red == 0) {
        data_ov015_0207e960->paletteFlags.increasing = 1;
    } else if (red == base.rgb.red) {
        data_ov015_0207e960->paletteFlags.increasing = 0;
    }

    context = data_ov015_0207e960;
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

    if (data_ov015_0207e960->paletteFlags.subEngine) {
        GXS_BeginLoadOBJExtPltt();
        *(volatile u16 *)0x068a0002 = data_ov015_0207e960->highlightColor.value;
        GXS_EndLoadOBJExtPltt();
    } else {
        GX_BeginLoadOBJExtPltt();
        *(volatile u16 *)0x06890002 = data_ov015_0207e960->highlightColor.value;
        GX_EndLoadOBJExtPltt();
    }
}
