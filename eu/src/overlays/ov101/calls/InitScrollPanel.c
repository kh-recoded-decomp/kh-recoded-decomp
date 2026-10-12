#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"
#include "src/overlays/ov101/ListMenuData.h"

typedef ListScrollPanelConfig ScrollPanelConfig;

typedef Ov101ScrollPanel ScrollPanel;

typedef struct {
    u8 pad_0000[0xCD6C];
    ScrollPanel panels[2];
} Ov101State;

extern s16 *GetOv101SlotEntryResource(int listIndex, int entryIndex, Ov101State *state);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 Fx32_Ceil(fx32 value);
extern void SetOv101SlotEntryVisible(int listIndex, int entryIndex, int visible, Ov101State *state);
extern void UpdateScrollPanel(int listId, Ov101State *state);

#define INT_TO_FX32_ROUNDED(v) ((fx32)((float)(v) > 0.0f ? 0.5f + 4096.0f * (float)(v) : 4096.0f * (float)(v) - 0.5f))

void InitScrollPanel(ScrollPanelConfig *config, Ov101State *state)
{
    ScrollPanel *panel;
    s16 *bounds;
    int length;
    fx32 lengthFx;
    fx32 ratio;

    panel = state->panels;
    panel += config->listId;
    panel->listId = config->listId;
    panel->pageRows = config->pageRows;
    panel->totalRows = config->totalRows;
    panel->cursorEntry = config->cursorEntry;
    panel->upArrowEntry = config->upArrowEntry;
    panel->downArrowEntry = config->downArrowEntry;
    panel->barEntry = config->barEntry;
    panel->unk_1C = config->thumbEntry;
    panel->unk_20 = config->firstPipEntry;
    panel->unk_24 = config->lastPipEntry;
    panel->unk_28 = config->barEndEntry;
    panel->scroll = 0;
    panel->cursor = 0;
    if (panel->barEntry >= 0) {
        bounds = GetOv101SlotEntryResource(panel->listId, panel->barEntry, state);
        panel->trackLength = bounds[1] - 0xf - bounds[3];
        panel->barMarginTop = 8;
        panel->barMarginBottom = 8;
        panel->barStep = 8;
        length = panel->trackLength - (panel->barMarginTop + panel->barMarginBottom);
        lengthFx = INT_TO_FX32_ROUNDED(length);
        ratio = FX_Div(INT_TO_FX32_ROUNDED(panel->pageRows), INT_TO_FX32_ROUNDED(panel->totalRows));
        if (ratio > FX32_ONE) {
            ratio = FX32_ONE;
        }
        panel->thumbLength = (fx32)(((s64)lengthFx * ratio + 0x800) >> 12);
        panel->thumbSteps = Fx32_Ceil(FX_Div(panel->thumbLength, 0x8000)) >> 12;
    }
    if (panel->upArrowEntry >= 0) {
        SetOv101SlotEntryVisible(panel->listId, panel->upArrowEntry, 0, state);
    }
    if (panel->totalRows <= panel->pageRows && panel->downArrowEntry >= 0) {
        SetOv101SlotEntryVisible(panel->listId, panel->downArrowEntry, 0, state);
    }
    UpdateScrollPanel(panel->listId, state);
}
