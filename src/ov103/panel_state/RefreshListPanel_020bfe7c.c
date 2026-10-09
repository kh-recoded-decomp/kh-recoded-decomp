#pragma opt_common_subs off
#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    int recordIndex;
    int x;
    int y;
    int pad[2];
} SpriteSlot;

typedef struct {
    int id;
    int visibleCount;
    int totalCount;
    int slotIndex;
    int arrowUpSlot;
    int arrowDownSlot;
    int barSlot;
    int thumbSlot;
    int firstTickSlot;
    int lastTickSlot;
    int capSlot;
    int scroll;
    int cursor;
    int barSpan;
    int marginTop;
    int marginBottom;
    int marginEnd;
    int thumbLength;
    int thumbStep;
} ListPanel;

typedef struct {
    char pad0[0xc9dc];
    SpriteSlot slots[11];
    char padSlots[0xcacc - 0xc9dc - 11 * 0x14];
    ListPanel lists[1];
} MenuWork;

extern SpriteSlot data_ov103_020c05e8[];
extern void SetSlotEntryVisible_020bf678(int listIndex, int entryIndex, int visible, MenuWork *work);
extern void SetSlotPosition_020bf7b4(int bank, int slotIndex, int x, int y, MenuWork *work);
extern int FX_Div_01ff9c84(int numer, int denom);

static inline SpriteSlot *GetTemplateSlot(int bank, int index)
{
    SpriteSlot *slot = &data_ov103_020c05e8[index];
    if (bank != 0) {
        slot = NULL;
    }
    return slot;
}

static inline void PlaceCap(ListPanel *panel, SpriteSlot *thumb, SpriteSlot *cap, MenuWork *work)
{
    SetSlotPosition_020bf7b4(panel->id, panel->capSlot, cap->x, thumb->y + 8 + (panel->thumbLength >> 12), work);
}

#define F32_TO_FX32(v) ((int)((v) > 0 ? 0.5f + 4096.0f * (v) : 4096.0f * (v) - 0.5f))

void RefreshListPanel_020bfe7c(int listIndex, MenuWork *work)
{
    int range;
    int travel;
    int i;
    int offset;
    int span;
    int scroll;
    int thumb;
    int bank;
    int visible;
    int total;
    SpriteSlot *slot;
    SpriteSlot *capSlot;
    ListPanel *list;

    list = work->lists;
    list += listIndex;
    if (list->arrowUpSlot >= 0) {
        if (list->scroll == 0) {
            SetSlotEntryVisible_020bf678(listIndex, list->arrowUpSlot, 0, work);
        } else {
            SetSlotEntryVisible_020bf678(listIndex, list->arrowUpSlot, 1, work);
        }
    }
    if (list->arrowDownSlot >= 0) {
        visible = list->visibleCount;
        total = list->totalCount;
        if (total == list->scroll + visible) {
            SetSlotEntryVisible_020bf678(listIndex, list->arrowDownSlot, 0, work);
        } else if (total > visible) {
            SetSlotEntryVisible_020bf678(listIndex, list->arrowDownSlot, 1, work);
        }
    }
    if (list->barSlot < 0) {
        return;
    }
    range = list->barSpan - (list->marginTop + list->marginEnd);
    travel = F32_TO_FX32((float)(range + 1)) - list->thumbLength;
    total = list->totalCount - list->visibleCount;
    span = F32_TO_FX32((float)total);
    scroll = list->scroll;
    offset = (int)(((s64)travel * FX_Div_01ff9c84(F32_TO_FX32((float)scroll), span) + 0x800) >> 12);
    thumb = list->thumbSlot;
    slot = NULL;
    if (listIndex == 0) {
        slot = &data_ov103_020c05e8[thumb];
    }
    SetSlotPosition_020bf7b4(list->id, thumb, slot->x, slot->y + (offset >> 12), work);
    for (i = list->firstTickSlot; i <= list->lastTickSlot; i++) {
        SpriteSlot *tick = GetTemplateSlot(listIndex, i);
        if (i - list->firstTickSlot <= list->thumbStep) {
            SetSlotEntryVisible_020bf678(list->id, i, 1, work);
        } else {
            SetSlotEntryVisible_020bf678(list->id, i, 0, work);
        }
        SetSlotPosition_020bf7b4(list->id, i, tick->x, tick->y + (offset >> 12), work);
    }
    bank = list->id;
    slot = bank == 0 ? &work->slots[list->thumbSlot] : NULL;
    capSlot = bank == 0 ? &work->slots[list->capSlot] : NULL;
    PlaceCap(list, slot, capSlot, work);
}
