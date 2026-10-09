#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? ((f32)(n) * 4096.0f + 0.5f) : ((f32)(n) * 4096.0f - 0.5f)))

typedef float f32;

typedef struct {
    int handle;
    int x;
    int y;
    u8 pad_0C[0x10];
} SlotItem;

typedef struct {
    u8 pad_00[8];
    int x;
    int y;
    u8 pad_10[0xc];
} SlotLayout;

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    u8 pad_0C[4];
    int headSlot;
    int tailSlot;
    int barSlot;
    int barLayout;
    int firstSlot;
    int lastSlot;
    int cursorSlot;
    int visibleCount;
    u8 pad_30[4];
    int trackLength;
    int trackStart;
    u8 pad_3C[4];
    int trackEnd;
    fx32 scroll;
    int litCount;
} ScrollBar;

typedef struct {
    u8 pad_0000[0xca68];
    SlotItem itemsA[13];
    SlotItem itemsB[13];
    u8 pad_cd40[0xcf54 - 0xcd40];
    ScrollBar bars[2];
} ListWork;

extern SlotLayout data_ov093_020c4108[];
extern SlotLayout data_ov093_020c4274[];

extern void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, ListWork *work);
extern void SetSlotPosition_020c0458(int side, int slotIndex, int x, int y, ListWork *work);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

static inline SlotItem *GetSlotItem(ListWork *work, int side, int slot)
{
    return side == 0 ? &work->itemsA[slot] : &work->itemsB[slot];
}

void RefreshScrollBar_020c0cb0(int index, ListWork *work)
{
    int slot;
    fx32 rangeFx;
    int range;
    int trackSpan;
    fx32 offset;
    fx32 countFx;
    int count;
    fx32 trackPos;
    SlotItem *cursorItem;
    SlotItem *barItem;
    SlotLayout *layout;
    ScrollBar *bar;

    bar = &work->bars[index];

    if (bar->headSlot >= 0) {
        if (bar->visibleCount == 0) {
            SetSlotAnimFlag_020c0310(index, bar->headSlot, 0, work);
        } else {
            SetSlotAnimFlag_020c0310(index, bar->headSlot, 1, work);
        }
    }
    if (bar->tailSlot >= 0) {
        if (bar->rangeEnd == bar->visibleCount + bar->rangeStart) {
            SetSlotAnimFlag_020c0310(index, bar->tailSlot, 0, work);
        } else if (bar->rangeEnd > bar->rangeStart) {
            SetSlotAnimFlag_020c0310(index, bar->tailSlot, 1, work);
        }
    }
    if (bar->barSlot < 0) {
        return;
    }

    trackSpan = bar->trackLength - (bar->trackStart + bar->trackEnd);
    trackPos = INT_TO_FX32(trackSpan + 1) - bar->scroll;
    range = bar->rangeEnd - bar->rangeStart;
    rangeFx = INT_TO_FX32(range);
    count = bar->visibleCount;
    countFx = INT_TO_FX32(count);
    offset = (fx32)(((s64)trackPos * FX_Div_01ff9c84(countFx, rangeFx) + 0x800) >> 12);

    if (index == 0) {
        layout = &data_ov093_020c4108[bar->barLayout];
    } else {
        layout = &data_ov093_020c4274[bar->barLayout];
    }
    SetSlotPosition_020c0458(bar->id, bar->barLayout, layout->x, layout->y + (offset >> 12), work);

    for (slot = bar->firstSlot; slot <= bar->lastSlot; slot++) {
        layout = (index == 0) ? &data_ov093_020c4108[slot] : &data_ov093_020c4274[slot];
        if (slot - bar->firstSlot <= bar->litCount) {
            SetSlotAnimFlag_020c0310(bar->id, slot, 1, work);
        } else {
            SetSlotAnimFlag_020c0310(bar->id, slot, 0, work);
        }
        SetSlotPosition_020c0458(bar->id, slot, layout->x, layout->y + (offset >> 12), work);
    }

    barItem = GetSlotItem(work, bar->id, bar->barLayout);
    cursorItem = GetSlotItem(work, bar->id, bar->cursorSlot);
    SetSlotPosition_020c0458(work->bars[index].id, bar->cursorSlot, cursorItem->x,
                             barItem->y + 8 + (bar->scroll >> 12), work);
}
