#include "src/overlays/ov001/FieldUiTables.h"

typedef struct PanelModeState {
    u8 reserved00[0x30];
    s32 active;
    u8 reserved34[4];
    s32 timer;
    u8 reserved3c[0xc];
    s32 isLanguage16;
    u8 reserved4c[0x84];
    s32 overlayId;
    const void *modeData;
    s32 mode;
    u8 reservedDc[4];
    s32 language;
} PanelModeState;

extern int func_02029f6c(void);

void Panel_InitFromModeTables(PanelModeState *state, int mode)
{
    PanelModeIdTable primary = gPanelPrimaryModeRecords;
    PanelModeDataTable secondary = gPanelModeDataPointers;

    state->overlayId = primary.values[mode];
    state->modeData = secondary.values[mode];
    state->mode = mode;
    state->active = 1;
    state->isLanguage16 = func_02029f6c() == 0x10;
    state->language = func_02029f6c();
    state->timer = 0;
}
