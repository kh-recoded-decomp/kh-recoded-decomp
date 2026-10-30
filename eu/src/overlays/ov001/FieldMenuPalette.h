#ifndef KH_RECODED_FIELD_MENU_PALETTE_H
#define KH_RECODED_FIELD_MENU_PALETTE_H

#include "src/overlays/ov001/FieldMenuPalettes.h"

/* Recovered ARM32 views, not complete allocation sizes. */
typedef struct FieldMenuPaletteView {
    u8 reserved00[0x68];
    s32 paletteMode;
    s32 previousPaletteMode;
    s8 fadeLevel;
    s8 fadeStep;
} FieldMenuPaletteView;

typedef struct FieldMenuPaletteHandleView {
    u32 state;
    FieldMenuPaletteView *menu;
    const u16 *palette;
    u16 fade[3];
} FieldMenuPaletteHandleView;

/* fade begins at the separately named BSS symbol data_ov001_020a04dc. */
extern FieldMenuPaletteHandleView data_ov001_020a04d0;

#endif
