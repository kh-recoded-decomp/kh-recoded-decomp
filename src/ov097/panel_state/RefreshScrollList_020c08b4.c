#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int handle;
    int visibleRows;
    int totalRows;
    int cursorSlot;
    int upArrowSlot;
    int downArrowSlot;
    int trackSlot;
    int thumbSlot;
    int firstDotSlot;
    int lastDotSlot;
    int thumbCapSlot;
    int scrollRow;
    int cursorRow;
    int trackSpan;
    int topMargin;
    int dotSpacing;
    int bottomMargin;
    fx32 thumbLength;
    int litDotCount;
} ScrollList;

typedef struct {
    int panelIndex;
    int x;
    int y;
    u8 pad_0c[0x10];
} PanelSlot;

typedef struct {
    u8 pad_00[8];
    int x;
    int y;
    u8 pad_10[0xc];
} PanelSlotDef;

typedef struct {
    u8 pad_0000[0x180];
    ScrollList lists[2];
    u8 pad_0218[0xca80 - 0x218];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

extern PanelSlotDef data_ov097_020c1ff0[];
extern PanelSlotDef data_ov097_020c22c4[];
extern void SetPanelSlotFlag_020bff94(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene);
extern void SetPanelSlotPosition_020c00fc(int listIndex, int slotIndex, int x, int y, MenuScene *scene);
extern int FX_Div_01ff9c84(int numer, int denom);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

void RefreshScrollList_020c08b4(int listIndex, MenuScene *scene)
{
    int i;
    int trackRows;
    int hiddenRows;
    PanelSlotDef *def;
    PanelSlot *thumb;
    PanelSlot *cap;
    fx32 range;
    fx32 offset;
    fx32 hidden;
    ScrollList *list = &scene->lists[listIndex];

    if (list->upArrowSlot >= 0) {
        if (list->scrollRow == 0) {
            SetPanelSlotFlag_020bff94(listIndex, list->upArrowSlot, FALSE, scene);
        } else {
            SetPanelSlotFlag_020bff94(listIndex, list->upArrowSlot, TRUE, scene);
        }
    }
    if (list->downArrowSlot >= 0) {
        if (list->totalRows == list->scrollRow + list->visibleRows) {
            SetPanelSlotFlag_020bff94(listIndex, list->downArrowSlot, FALSE, scene);
        } else if (list->totalRows > list->visibleRows) {
            SetPanelSlotFlag_020bff94(listIndex, list->downArrowSlot, TRUE, scene);
        }
    }
    if (list->trackSlot < 0) {
        return;
    }
    trackRows = list->trackSpan - (list->topMargin + list->bottomMargin);
    range = ROW_TO_FX32(trackRows + 1) - list->thumbLength;
    hiddenRows = list->totalRows - list->visibleRows;
    hidden = ROW_TO_FX32(hiddenRows);
    offset = FxMul(range, FX_Div_01ff9c84(ROW_TO_FX32(list->scrollRow), hidden));
    def = &(listIndex == 1 ? data_ov097_020c22c4 : data_ov097_020c1ff0)[list->thumbSlot];
    SetPanelSlotPosition_020c00fc(list->handle, list->thumbSlot, def->x, def->y + (offset >> 12), scene);
    for (i = list->firstDotSlot; i <= list->lastDotSlot; i++) {
        if (listIndex == 1) {
            def = &data_ov097_020c22c4[i];
        } else {
            def = &data_ov097_020c1ff0[i];
        }
        if (i - list->firstDotSlot <= list->litDotCount) {
            SetPanelSlotFlag_020bff94(list->handle, i, TRUE, scene);
        } else {
            SetPanelSlotFlag_020bff94(list->handle, i, FALSE, scene);
        }
        SetPanelSlotPosition_020c00fc(list->handle, i, def->x, def->y + (offset >> 12), scene);
    }
    if (scene->lists[listIndex].handle == 1) {
        thumb = &scene->subSlots[list->thumbSlot];
    } else {
        thumb = &scene->mainSlots[list->thumbSlot];
    }
    if (scene->lists[listIndex].handle == 1) {
        cap = &scene->subSlots[list->thumbCapSlot];
    } else {
        cap = &scene->mainSlots[list->thumbCapSlot];
    }
    SetPanelSlotPosition_020c00fc(list->handle, list->thumbCapSlot, cap->x, thumb->y + 8 + (list->thumbLength >> 12), scene);
}
