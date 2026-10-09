#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef float f32;

typedef struct {
    int slotIndex;
    int x;
    int y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    int cellId;
    int animId;
    int x;
    int y;
    int priority;
    int flags;
} SlotTemplate;

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
} ScrollPanel;

typedef struct {
    u8 pad_00[0x17c];
    u8 screenObjects[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
    u8 pad_cc84[0xcd64 - 0xcc84];
    ScrollPanel lists[2];
} Ov101State;

extern SlotTemplate data_ov101_020c0f38[];
extern SlotTemplate data_ov101_020c1198[];
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void SetSlotEntryVisible_020bfa6c(int screen, int panelIndex, int value, Ov101State *state);
extern void SetSlotEntryPosition_020bfbc4(int screen, int panelIndex, int x, int y, Ov101State *state);

void UpdateScrollPanel_020c0274(int panelIndex, Ov101State *state)
{
    int i;
    fx32 offset;
    ScrollPanel *lists;
    ScrollPanel *list;
    SlotTemplate *layout;
    SlotEntry *barEnd;
    int screen;
    SlotEntry *thumb;
    fx32 travel;
    fx32 range;
    int span;
    int count;

    lists = state->lists;
    list = &lists[panelIndex];
    if (list->upArrowPanel >= 0) {
        if (list->topRow == 0) {
            SetSlotEntryVisible_020bfa6c(panelIndex, list->upArrowPanel, FALSE, state);
        } else {
            SetSlotEntryVisible_020bfa6c(panelIndex, list->upArrowPanel, TRUE, state);
        }
    }
    if (list->downArrowPanel >= 0) {
        if (list->totalRows == list->topRow + list->visibleRows) {
            SetSlotEntryVisible_020bfa6c(panelIndex, list->downArrowPanel, FALSE, state);
        } else if (list->totalRows > list->visibleRows) {
            SetSlotEntryVisible_020bfa6c(panelIndex, list->downArrowPanel, TRUE, state);
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
    layout = panelIndex == 0 ? data_ov101_020c0f38 : data_ov101_020c1198;
    SetSlotEntryPosition_020bfbc4(list->id, list->thumbPanel, layout[list->thumbPanel].x,
                                 layout[list->thumbPanel].y + (offset >> 12), state);
    for (i = list->firstPipPanel; i <= list->lastPipPanel; i++) {
        if (panelIndex == 0) {
            layout = &data_ov101_020c0f38[i];
        } else {
            layout = &data_ov101_020c1198[i];
        }
        if (i - list->firstPipPanel <= list->thumbSteps) {
            SetSlotEntryVisible_020bfa6c(list->id, i, TRUE, state);
        } else {
            SetSlotEntryVisible_020bfa6c(list->id, i, FALSE, state);
        }
        SetSlotEntryPosition_020bfbc4(list->id, i, layout->x, layout->y + (offset >> 12), state);
    }
    screen = *(u32 *)&list->id;
    thumb = screen == 0 ? &state->primaryEntries[list->thumbPanel] : &state->secondaryEntries[list->thumbPanel];
    barEnd = screen == 0 ? &state->primaryEntries[list->barEndPanel] : &state->secondaryEntries[list->barEndPanel];
    SetSlotEntryPosition_020bfbc4(list->id, list->barEndPanel, barEnd->x, thumb->y + 8 + (list->thumbLength >> 12), state);
}
