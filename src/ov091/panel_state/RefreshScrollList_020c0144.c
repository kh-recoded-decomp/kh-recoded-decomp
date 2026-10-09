#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef float f32;

typedef struct {
    int slotIndex;
    int x;
    int y;
    u8 pad_0C[0x8];
} ListPanel;

typedef struct {
    int cellId;
    int animId;
    int x;
    int y;
    int priority;
    int flags;
} PanelLayout;

typedef struct {
    int id;
    int visibleRows;
    int totalRows;
    int panelIndex;
    int upArrowPanel;
    int downArrowPanel;
    int scrollBarPanel;
    int thumbPanel;
    int firstPipPanel;
    int lastPipPanel;
    int barEndPanel;
    int topRow;
    int cursorRow;
    int barLength;
    int topMargin;
    int bottomMargin;
    int thumbMargin;
    fx32 thumbLength;
    int thumbSteps;
} ScrollList;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
    u8 pad_ca4c[0xcbd0 - 0xca4c];
    ScrollList lists[1];
} MenuScene;

extern PanelLayout data_ov091_020c2bb4[];
extern PanelLayout data_ov091_020c3724[];
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void SetListPanelSlotFlag_020bf918(int screen, int panelIndex, int value, MenuScene *scene);
extern void SetListPanelSlotPos_020bfaa0(int screen, int panelIndex, int x, int y, MenuScene *scene);

void RefreshScrollList_020c0144(int listIndex, MenuScene *scene)
{
    int i;
    fx32 offset;
    ScrollList *lists;
    ScrollList *list;
    PanelLayout *layout;
    ListPanel *barEnd;
    int screen;
    ListPanel *thumb;
    fx32 travel;
    fx32 range;
    int span;
    int count;

    lists = scene->lists;
    list = &lists[listIndex];
    if (list->upArrowPanel >= 0) {
        if (list->topRow == 0) {
            SetListPanelSlotFlag_020bf918(listIndex, list->upArrowPanel, FALSE, scene);
        } else {
            SetListPanelSlotFlag_020bf918(listIndex, list->upArrowPanel, TRUE, scene);
        }
    }
    if (list->downArrowPanel >= 0) {
        if (list->totalRows == list->topRow + list->visibleRows) {
            SetListPanelSlotFlag_020bf918(listIndex, list->downArrowPanel, FALSE, scene);
        } else if (list->totalRows > list->visibleRows) {
            SetListPanelSlotFlag_020bf918(listIndex, list->downArrowPanel, TRUE, scene);
        }
    }
    if (list->scrollBarPanel < 0) {
        return;
    }
    span = list->barLength - (list->topMargin + list->thumbMargin) + 1;
    travel = INT_TO_FX32(span) - list->thumbLength;
    count = list->totalRows - list->visibleRows;
    range = INT_TO_FX32(count);
    offset = (fx32)(((s64)travel * FX_Div_01ff9c84(INT_TO_FX32(list->topRow), range) + 0x800) >> 12);
    layout = listIndex == 0 ? data_ov091_020c2bb4 : data_ov091_020c3724;
    SetListPanelSlotPos_020bfaa0(list->id, list->thumbPanel, layout[list->thumbPanel].x,
                                 layout[list->thumbPanel].y + (offset >> 12), scene);
    for (i = list->firstPipPanel; i <= list->lastPipPanel; i++) {
        if (listIndex == 0) {
            layout = &data_ov091_020c2bb4[i];
        } else {
            layout = &data_ov091_020c3724[i];
        }
        if (i - list->firstPipPanel <= list->thumbSteps) {
            SetListPanelSlotFlag_020bf918(list->id, i, TRUE, scene);
        } else {
            SetListPanelSlotFlag_020bf918(list->id, i, FALSE, scene);
        }
        SetListPanelSlotPos_020bfaa0(list->id, i, layout->x, layout->y + (offset >> 12), scene);
    }
    screen = *(u32 *)&list->id;
    thumb = screen == 0 ? &scene->topPanels[list->thumbPanel] : &scene->bottomPanels[list->thumbPanel];
    barEnd = screen == 0 ? &scene->topPanels[list->barEndPanel] : &scene->bottomPanels[list->barEndPanel];
    SetListPanelSlotPos_020bfaa0(list->id, list->barEndPanel, barEnd->x, thumb->y + 8 + (list->thumbLength >> 12), scene);
}
