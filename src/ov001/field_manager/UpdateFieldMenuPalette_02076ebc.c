#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x68];
    s32 paletteMode;
    s32 prevPaletteMode;
    s8 fadeLevel;
    s8 fadeStep;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
    const u16 *palette;
    u16 fade[3];
} FieldMenuHandle;

typedef struct {
    u16 base[3];
    u16 highlight[3];
} FieldMenuFadeColors;

extern FieldMenuHandle data_ov001_020a04b0;
extern u16 data_ov001_0209ee40[];
extern u16 data_ov001_0209ee46[3];
extern u16 data_ov001_0209ee4c[3];
extern FieldMenuFadeColors FieldMenuFadeColors_0209ee40;
extern char FieldMenuFadeWhite_000003ff[];

extern u16 LerpColor555_02076e30(u16 fromColor, int toColor, int step, u16 stepCount);
extern void GFXi_EnqueueCommand_02014090(int command, int offset, const void *src, int size);

void UpdateFieldMenuPalette_02076ebc(FieldMenu *menu, BOOL advance) {
    BOOL restore = FALSE;
    FieldMenuHandle *handle = &data_ov001_020a04b0;
    const u16 *palette;

    if (menu->paletteMode == -1) {
        menu->paletteMode = menu->prevPaletteMode;
        restore = TRUE;
    }
    switch (menu->paletteMode) {
    case 0:
    case 7:
        handle->palette = palette = data_ov001_0209ee46;
        break;
    case 11:
    case 13:
        if (menu->prevPaletteMode != menu->paletteMode) {
            menu->fadeLevel = 0;
            menu->fadeStep = 2;
            handle->palette = palette = data_ov001_0209ee46;
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
        handle->fade[0] = LerpColor555_02076e30(FieldMenuFadeColors_0209ee40.highlight[0], 0x210, menu->fadeLevel, 8);
        handle->fade[1] = LerpColor555_02076e30(FieldMenuFadeColors_0209ee40.highlight[1], 0x318, menu->fadeLevel, 8);
        // Absolute symbol keeps white a pool literal
        handle->fade[2] = LerpColor555_02076e30(FieldMenuFadeColors_0209ee40.highlight[2],
                                                (int)FieldMenuFadeWhite_000003ff, menu->fadeLevel, 8);
        handle->palette = palette = data_ov001_020a04b0.fade;
        break;
    case 10:
        handle->palette = palette = data_ov001_0209ee40;
        break;
    default:
        handle->palette = palette = data_ov001_0209ee4c;
        break;
    }
    handle = &data_ov001_020a04b0;
    if (restore) {
        menu->paletteMode = -1;
        GFXi_EnqueueCommand_02014090(0xf, 0x138, palette, 6);
    } else {
        menu->prevPaletteMode = menu->paletteMode;
        GFXi_EnqueueCommand_02014090(0xf, 0x138, palette, 6);
    }
    GFXi_EnqueueCommand_02014090(0xf, 0x158, handle->palette, 6);
}
