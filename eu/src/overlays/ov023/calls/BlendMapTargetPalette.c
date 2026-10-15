#include "src/overlays/ov023/MapTargetPalette.h"

extern BOOL NNS_GfdRegisterNewVramTransferTask(int kind, u32 destination, const void *source, u32 size);

void BlendMapTargetPalette(MapTargetPaletteState *menu, int blend)
{
    int i;
    const u16 *source;
    const u16 *target;
    int index = menu->paletteIndex - 1;
    if (index <= 0) {
        index = 0;
    }
    source = gMapTargetBasePalettes[index];
    target = gMapTargetHighlightPalette;
    for (i = 0; i < 4; ++i) {
        u16 red = *source & 0x1f;
        u16 green = (*source & 0x3e0) >> 5;
        u16 blue = (*source & 0x7c00) >> 10;
        ++source;
        u16 endColor = *target;
        u16 targetBlue = (endColor & 0x7c00) >> 10;
        u16 targetRed;
        u16 targetGreen;
        u32 blueBits;
        blueBits = blue + (targetBlue - blue) * blend / 16;
        blueBits = (u16)blueBits << 10;
        targetRed = endColor & 0x1f;
        red += (targetRed - red) * blend / 16;
        targetGreen = (endColor & 0x3e0) >> 5;
        ++target;
        green += (targetGreen - green) * blend / 16;
        gMapTargetPaletteWork[i] = red | (green << 5) | blueBits;
    }
    /* Engine-B OBJ palette: leave transparent color zero untouched. */
    NNS_GfdRegisterNewVramTransferTask(30, 2, gMapTargetPaletteWork, 8);
}
