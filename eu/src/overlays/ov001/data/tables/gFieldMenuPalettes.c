#include "src/overlays/ov001/FieldMenuPalettes.h"

FieldMenuStateRamps gFieldMenuStateRamps = {
    {0x2840, 0x54c1, 0x6d24},
    {0x006f, 0x04b7, 0x0cfe},
    {0x00c0, 0x11a0, 0x1a60}
};

u16 gFieldMenuNormalRamps[2][3] = {
    {0x5d23, 0x71a5, 0x7e29},
    {0x00c0, 0x11a0, 0x1a60}
};
u16 gFieldMenuAlternateRamps[2][3] = {
    {0x7b15, 0x7f56, 0x7f99},
    {0x63d5, 0x6bf6, 0x73f9}
};

u16 gFieldMenuModeBackgroundPalettes[3][4] = {
    {0x2840, 0x54c1, 0x6d24, 0x7ed2},
    {0x00c0, 0x11a0, 0x1a60, 0x27f4},
    {0x2840, 0x54c1, 0x6d24, 0x7ed2}
};
u16 gFieldMenuModeHighlightPalettes[3][4] = {
    {0x5d23, 0x71a5, 0x7e29, 0x7f14},
    {0x1a21, 0x2b02, 0x3761, 0x37f6},
    {0x5d23, 0x71a5, 0x7e29, 0x7f14}
};

#pragma define_section fieldPaletteAlignment ".data" RW
/* Two retained alignment bytes before gFieldMenuTaskDescriptor. */
__declspec(fieldPaletteAlignment) u8 gFieldMenuPaletteDataAlignment[2] = {0, 0};
