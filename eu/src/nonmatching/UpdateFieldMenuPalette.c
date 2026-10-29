/* Pending func_ov001_02076ebc; excluded from the linked build and C coverage. */
#include "src/overlays/ov001/FieldMenuPalette.h"

extern u16 func_ov001_02076e30(u16 from, u16 to, int level, u16 maxLevel);
extern BOOL NNS_GfdRegisterNewVramTransferTask(u32 type, u32 destination,
                                             const void *source, u32 size);

void UpdateFieldMenuPalette(FieldMenuPaletteView *menu, BOOL advance)
{
    BOOL restore = FALSE;
    FieldMenuPaletteHandleView *handle = &data_ov001_020a04d0;
    const u16 *palette;

    /* -1 temporarily selects the previous mode, then restores the sentinel. */
    if (menu->paletteMode == -1) {
        menu->paletteMode = menu->previousPaletteMode;
        restore = TRUE;
    }
    switch (menu->paletteMode) {
    case 0:
    case 7:
        handle->palette = palette = gFieldMenuStateRamps[FIELD_MENU_RAMP_RED];
        break;
    case 11:
    case 13:
        if (menu->previousPaletteMode != menu->paletteMode) {
            menu->fadeLevel = 0;
            menu->fadeStep = 2;
            handle->palette = palette = gFieldMenuStateRamps[FIELD_MENU_RAMP_RED];
            break;
        }
        if (menu->fadeLevel >= 8) {
            menu->fadeStep = -2;
        } else if (menu->fadeLevel <= 0) {
            menu->fadeStep = 2;
        }
        if (advance) {
            /* The ROM stores the signed byte before applying the clamp. */
            menu->fadeLevel = (s8)(u8)(menu->fadeLevel + menu->fadeStep);
            menu->fadeLevel = menu->fadeLevel > 8 ? 8 :
                              menu->fadeLevel < 0 ? 0 : menu->fadeLevel;
        }
        handle->fade[0] = func_ov001_02076e30(
            gFieldMenuStateRamps[FIELD_MENU_RAMP_RED][0], 0x0210, menu->fadeLevel, 8);
        handle->fade[1] = func_ov001_02076e30(
            gFieldMenuStateRamps[FIELD_MENU_RAMP_RED][1], 0x0318, menu->fadeLevel, 8);
        /* RGB555 yellow (31,31,0), a real integer constant. */
        handle->fade[2] = func_ov001_02076e30(
            gFieldMenuStateRamps[FIELD_MENU_RAMP_RED][2], 0x03ff, menu->fadeLevel, 8);
        handle->palette = palette = data_ov001_020a04d0.fade;
        break;
    case 10:
        handle->palette = palette = gFieldMenuStateRamps[FIELD_MENU_RAMP_BLUE];
        break;
    default:
        handle->palette = palette = gFieldMenuStateRamps[FIELD_MENU_RAMP_GREEN];
        break;
    }
    if (restore) {
        menu->paletteMode = -1;
    } else {
        menu->previousPaletteMode = menu->paletteMode;
    }
    NNS_GfdRegisterNewVramTransferTask(15, 0x138, palette, 6);
    /* Reload after the first queue call, as the original function does. */
    NNS_GfdRegisterNewVramTransferTask(15, 0x158, handle->palette, 6);
}
