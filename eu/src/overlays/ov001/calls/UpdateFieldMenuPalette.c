#include "src/overlays/ov001/FieldMenuPalette.h"

extern u16 LerpColor555_02076e30(u16 from, int to, int level, u16 maxLevel);
extern BOOL NNS_GfdRegisterNewVramTransferTask(u32 type, u32 destination, const void *source, u32 size);

/*
 * Steering symbols (docs/PROGRESS_POLICY.md): the original keeps the ramp table's address in
 * r7 for the three fade reads and loads yellow 0x3ff from its literal pool, with a second pool
 * word for the same table address. Written plainly, mwcc derives 0x3ff from 0x318 (`adds #0xe7`),
 * spends r7 on that and merges the two pool words. A second name for the table and the colour
 * as a linker-absolute symbol (both in tools/configure.py) reproduce the original; the
 * original spelling is unknown. The lerp is declared with an `int` target here so the
 * symbol's address passes unchanged.
 */
extern const FieldMenuStateRamps gFieldMenuFadeRamps;   /* = gFieldMenuStateRamps */
extern char FieldMenuFadeYellow[];                       /* = 0x3ff, RGB555 (31, 31, 0) */

/*
 * Pick the field menu's palette for its mode and queue it for both menu screens. Modes 11 and
 * 13 pulse the red ramp toward yellow, eight steps each way; mode -1 shows the previous mode
 * once and keeps the sentinel.
 */
void UpdateFieldMenuPalette(FieldMenuPaletteView *menu, BOOL advance)
{
    BOOL restore = FALSE;
    FieldMenuPaletteHandleView *handle = &data_ov001_020a04d0;
    const u16 *palette;

    if (menu->paletteMode == -1) {
        menu->paletteMode = menu->previousPaletteMode;
        restore = TRUE;
    }
    switch (menu->paletteMode) {
    case 0:
    case 7:
        handle->palette = palette = gFieldMenuStateRamps.red;
        break;
    case 11:
    case 13:
        if (menu->previousPaletteMode != menu->paletteMode) {
            menu->fadeLevel = 0;
            menu->fadeStep = 2;
            handle->palette = palette = gFieldMenuStateRamps.red;
            break;
        }
        if (menu->fadeLevel >= 8) {
            menu->fadeStep = -2;
        } else if (menu->fadeLevel <= 0) {
            menu->fadeStep = 2;
        }
        if (advance) {
            menu->fadeLevel += menu->fadeStep;
            menu->fadeLevel = menu->fadeLevel > 8 ? 8 : menu->fadeLevel < 0 ? 0 : menu->fadeLevel;
        }
        handle->fade[0] = LerpColor555_02076e30(gFieldMenuFadeRamps.red[0], 0x0210, menu->fadeLevel, 8);
        handle->fade[1] = LerpColor555_02076e30(gFieldMenuFadeRamps.red[1], 0x0318, menu->fadeLevel, 8);
        handle->fade[2] = LerpColor555_02076e30(gFieldMenuFadeRamps.red[2], (int)FieldMenuFadeYellow,
                                                menu->fadeLevel, 8);
        handle->palette = palette = data_ov001_020a04d0.fade;
        break;
    case 10:
        handle->palette = palette = gFieldMenuStateRamps.blue;
        break;
    default:
        handle->palette = palette = gFieldMenuStateRamps.green;
        break;
    }
    handle = &data_ov001_020a04d0;
    if (restore) {
        menu->paletteMode = -1;
        NNS_GfdRegisterNewVramTransferTask(15, 0x138, palette, 6);
    } else {
        menu->previousPaletteMode = menu->paletteMode;
        NNS_GfdRegisterNewVramTransferTask(15, 0x138, palette, 6);
    }
    NNS_GfdRegisterNewVramTransferTask(15, 0x158, handle->palette, 6);
}
