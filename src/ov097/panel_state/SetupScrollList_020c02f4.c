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
} ScrollListDesc;

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
    u8 pad_000[0x180];
    ScrollList lists[2];
} MenuScene;

extern s16 *GetPanelSlotRecordData_020c0264(int listIndex, int slotIndex, MenuScene *scene);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u32 AlignUpTo4K_020c02d4(u32 size);
extern void SetPanelSlotFlag_020bff94(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene);
extern void RefreshScrollList_020c08b4(int listIndex, MenuScene *scene);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void SetupScrollList_020c02f4(ScrollListDesc *desc, MenuScene *scene)
{
    ScrollList *lists;
    ScrollList *list;
    int handle;
    s16 *bounds;
    int trackLength;
    fx32 ratio;

    lists = scene->lists;
    handle = desc->handle;
    lists[handle].handle = handle;
    list = &lists[handle];
    list->visibleRows = desc->visibleRows;
    list->totalRows = desc->totalRows;
    list->cursorSlot = desc->cursorSlot;
    list->upArrowSlot = desc->upArrowSlot;
    list->downArrowSlot = desc->downArrowSlot;
    list->trackSlot = desc->trackSlot;
    list->thumbSlot = desc->thumbSlot;
    list->firstDotSlot = desc->firstDotSlot;
    list->lastDotSlot = desc->lastDotSlot;
    list->thumbCapSlot = desc->thumbCapSlot;
    list->scrollRow = 0;
    list->cursorRow = 0;
    if (list->trackSlot >= 0) {
        bounds = GetPanelSlotRecordData_020c0264(list->handle, list->trackSlot, scene);
        list->trackSpan = bounds[1] - 15 - bounds[3];
        list->topMargin = 8;
        list->dotSpacing = 8;
        list->bottomMargin = 8;
        trackLength = ROW_TO_FX32(list->trackSpan - (list->topMargin + list->bottomMargin));
        ratio = FX_Div_01ff9c84(ROW_TO_FX32(list->visibleRows), ROW_TO_FX32(list->totalRows));
        if (ratio > 0x1000) {
            ratio = 0x1000;
        }
        list->thumbLength = (fx32)(((s64)trackLength * ratio + 0x800) >> 12);
        list->litDotCount = (int)AlignUpTo4K_020c02d4(FX_Div_01ff9c84(list->thumbLength, 0x8000)) >> 12;
    }
    if (list->upArrowSlot >= 0) {
        SetPanelSlotFlag_020bff94(list->handle, list->upArrowSlot, FALSE, scene);
    }
    if (list->totalRows <= list->visibleRows && list->downArrowSlot >= 0) {
        SetPanelSlotFlag_020bff94(list->handle, list->downArrowSlot, FALSE, scene);
    }
    RefreshScrollList_020c08b4(list->handle, scene);
}
