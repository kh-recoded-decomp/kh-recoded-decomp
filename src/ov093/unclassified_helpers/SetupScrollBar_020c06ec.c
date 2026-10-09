#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef float f32;

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? ((f32)(n) * 4096.0f + 0.5f) : ((f32)(n) * 4096.0f - 0.5f)))

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    int unk_0C;
    int headSlot;
    int tailSlot;
    int barSlot;
    int barLayout;
    int firstSlot;
    int lastSlot;
    int cursorSlot;
} ScrollBarDesc;

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    int unk_0C;
    int headSlot;
    int tailSlot;
    int barSlot;
    int barLayout;
    int firstSlot;
    int lastSlot;
    int cursorSlot;
    int scrollPos;
    int unk_30;
    int trackLength;
    int trackStart;
    int trackGap;
    int trackEnd;
    fx32 thumbLength;
    int thumbTiles;
} ScrollBar;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} SlotRect;

typedef struct {
    u8 pad_0000[0xcf54];
    ScrollBar bars[2];
} SceneWork;

extern SlotRect *GetSlotAnimResource_020c0680(int id, int slot, SceneWork *work);
extern void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, SceneWork *work);
extern void RefreshScrollBar_020c0cb0(int index, SceneWork *work);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 CeilFx32_020beb00(fx32 value);

void SetupScrollBar_020c06ec(ScrollBarDesc *desc, SceneWork *work)
{
    fx32 ratio;
    fx32 length;
    SlotRect *rect;
    ScrollBar *bar;
    ScrollBar *bars;
    int id;

    bars = work->bars;
    id = desc->id;
    bars[id].id = id;
    bar = &bars[id];
    bar->rangeStart = desc->rangeStart;
    bar->rangeEnd = desc->rangeEnd;
    bar->unk_0C = desc->unk_0C;
    bar->headSlot = desc->headSlot;
    bar->tailSlot = desc->tailSlot;
    bar->barSlot = desc->barSlot;
    bar->barLayout = desc->barLayout;
    bar->firstSlot = desc->firstSlot;
    bar->lastSlot = desc->lastSlot;
    bar->cursorSlot = desc->cursorSlot;
    bar->scrollPos = 0;
    bar->unk_30 = 0;
    if (bar->barSlot >= 0) {
        rect = GetSlotAnimResource_020c0680(bar->id, bar->barSlot, work);
        bar->trackLength = rect->y - 15 - rect->height;
        bar->trackStart = 8;
        bar->trackGap = 8;
        bar->trackEnd = 8;
        length = INT_TO_FX32(bar->trackLength - (bar->trackStart + bar->trackGap));
        ratio = FX_Div_01ff9c84(INT_TO_FX32(bar->rangeStart), INT_TO_FX32(bar->rangeEnd));
        if (ratio > 0x1000) {
            ratio = 0x1000;
        }
        bar->thumbLength = (fx32)(((fx64)length * ratio + 0x800) >> 12);
        bar->thumbTiles = CeilFx32_020beb00(FX_Div_01ff9c84(bar->thumbLength, 0x8000)) >> 12;
    }
    if (bar->headSlot >= 0) {
        SetSlotAnimFlag_020c0310(bar->id, bar->headSlot, 0, work);
    }
    if (bar->rangeEnd <= bar->rangeStart && bar->tailSlot >= 0) {
        SetSlotAnimFlag_020c0310(bar->id, bar->tailSlot, 0, work);
    }
    RefreshScrollBar_020c0cb0(bar->id, work);
}
