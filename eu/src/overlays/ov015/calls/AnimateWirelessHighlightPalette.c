#pragma opt_propagation off
#pragma opt_common_subs off
#include "nitro/types.h"

typedef union WirelessPaletteColor {
    u16 value;
    struct {
        u16 red : 5;
        u16 green : 5;
        u16 blue : 5;
        u16 unused : 1;
    } rgb;
} WirelessPaletteColor;

typedef struct WirelessPaletteContext {
    u8 reserved00[0xc2];
    WirelessPaletteColor baseColor;
    WirelessPaletteColor highlightColor;
    u8 reservedc6[0x1c];
    struct {
        u8 increasing : 1;
        u8 enabled : 1;
        u8 subEngine : 1;
        u8 reserved : 5;
    } paletteFlags;
} WirelessPaletteContext;

typedef char WirelessPaletteColorSizeCheck[
    sizeof(WirelessPaletteColor) == sizeof(u16) ? 1 : -1];

extern WirelessPaletteContext *data_ov015_0207e960;
extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_EndLoadOBJExtPltt(void);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);

void AnimateWirelessHighlightPalette(void)
{
    WirelessPaletteContext *context;
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
