#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

#define TO_FX32(v) ((fx32)(((f32)(v) > 0) ? (4096.0f * (f32)(v) + 0.5f) : (4096.0f * (f32)(v) - 0.5f)))

typedef struct {
    u8 pad_00[8];
    int x;
    int y;
    u8 pad_10[8];
} SlotLayout;

typedef struct {
    int objIndex;
    int x;
    int y;
    u8 pad_0c[8];
} SlotEntry;

typedef struct {
    int id;
    int pageSize;
    int itemCount;
    int cursorSlot;
    int upArrowSlot;
    int downArrowSlot;
    int barSlot;
    int thumbSlot;
    int firstItemSlot;
    int lastItemSlot;
    int barEndSlot;
    int scrollTop;
    int cursorRow;
    int trackHeight;
    int topMargin;
    int thumbWidth;
    int bottomMargin;
    fx32 thumbLength;
    int thumbSteps;
} ListState;

typedef struct {
    u8 pad_0000[0xCCC4];
    SlotEntry topSlots[21];
    SlotEntry bottomSlots[21];
    u8 pad_d00c[0xD054 - 0xD00C];
    ListState lists[2];
} ViewerWork;

extern SlotLayout data_ov099_020c255c[];
extern SlotLayout data_ov099_020c238c[];
extern void SetSlotObjVisible_020c0820(int screen, int slot, int visible, ViewerWork *work);
extern void SetSlotObjPosition_020c0964(int screen, int slot, int posX, int posY, ViewerWork *work);
extern int FX_Div_01ff9c84(int numer, int denom);

static inline SlotEntry *GetSlotEntry(ViewerWork *work, ListState *list, int *slot)
{
    return *(int *)list == 0 ? &work->topSlots[*slot] : &work->bottomSlots[*slot];
}

void UpdateScrollList_020c11b4(int screen, ViewerWork *work)
{
    int i;
    fx32 offset;
    fx32 range;
    fx32 travel;
    SlotEntry *endEntry;
    SlotEntry *thumbEntry;
    SlotLayout *layout;
    ListState *lists;
    ListState *list;
    int span;
    int count;

    lists = work->lists;
    list = &lists[screen];
    if (list->upArrowSlot >= 0) {
        if (list->scrollTop == 0) {
            SetSlotObjVisible_020c0820(screen, list->upArrowSlot, FALSE, work);
        } else {
            SetSlotObjVisible_020c0820(screen, list->upArrowSlot, TRUE, work);
        }
    }
    if (list->downArrowSlot >= 0) {
        if (list->itemCount == list->scrollTop + list->pageSize) {
            SetSlotObjVisible_020c0820(screen, list->downArrowSlot, FALSE, work);
        } else if (list->itemCount > list->pageSize) {
            SetSlotObjVisible_020c0820(screen, list->downArrowSlot, TRUE, work);
        }
    }
    if (list->barSlot < 0) {
        return;
    }
    span = list->trackHeight - (list->topMargin + list->bottomMargin) + 1;
    travel = TO_FX32(span) - list->thumbLength;
    count = list->itemCount - list->pageSize;
    range = TO_FX32(count);
    offset = (fx32)(((s64)travel * FX_Div_01ff9c84(TO_FX32(list->scrollTop), range) + 0x800) >> FX32_SHIFT);

    layout = (screen == 0) ? &data_ov099_020c255c[list->thumbSlot] : &data_ov099_020c238c[list->thumbSlot];
    SetSlotObjPosition_020c0964(list->id, list->thumbSlot, layout->x, layout->y + (offset >> FX32_SHIFT), work);

    for (i = list->firstItemSlot; i <= list->lastItemSlot; i++) {
        if (screen == 0) {
            layout = &data_ov099_020c255c[i];
        } else {
            layout = &data_ov099_020c238c[i];
        }
        if (i - list->firstItemSlot <= list->thumbSteps) {
            SetSlotObjVisible_020c0820(list->id, i, TRUE, work);
        } else {
            SetSlotObjVisible_020c0820(list->id, i, FALSE, work);
        }
        SetSlotObjPosition_020c0964(list->id, i, layout->x, layout->y + (offset >> FX32_SHIFT), work);
    }
    thumbEntry = GetSlotEntry(work, list, &list->thumbSlot);
    endEntry = GetSlotEntry(work, list, &list->barEndSlot);
    SetSlotObjPosition_020c0964(list->id, list->barEndSlot, endEntry->x, thumbEntry->y + 8 + (list->thumbLength >> FX32_SHIFT), work);
}
