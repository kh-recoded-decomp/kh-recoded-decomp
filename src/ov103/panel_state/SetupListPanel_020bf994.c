#include "nitro/types.h"

typedef struct {
    int id;
    int visibleCount;
    int totalCount;
    int slotIndex;
    int arrowUpSlot;
    int arrowDownSlot;
    int barSlot;
    int field1c;
    int field20;
    int field24;
    int field28;
} ListDesc;

typedef struct {
    int id;
    int visibleCount;
    int totalCount;
    int slotIndex;
    int arrowUpSlot;
    int arrowDownSlot;
    int barSlot;
    int field1c;
    int field20;
    int field24;
    int field28;
    int scroll;
    int cursor;
    int barSpan;
    int marginTop;
    int marginBottom;
    int field40;
    int thumbLength;
    int thumbStep;
} ListPanel;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} SlotRect;

typedef struct {
    char pad0[0xcacc];
    ListPanel lists[1];
} MenuWork;

extern SlotRect *func_ov103_020bf8c0(int listId, int slot, MenuWork *work);
extern void func_ov103_020bf678(int listId, int slot, int frame, MenuWork *work);
extern void func_ov103_020bfe7c(int listId, MenuWork *work);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u32 AlignUpTo4K_020beb00(u32 size);

#define F32_TO_FX32(v) ((int)((v) > 0 ? 0.5f + 4096.0f * (v) : 4096.0f * (v) - 0.5f))

void SetupListPanel_020bf994(ListDesc *desc, MenuWork *work)
{
    SlotRect *rect;
    int travel;
    int ratio;
    ListPanel *list;

    list = work->lists;
    list += desc->id;
    list->id = desc->id;
    list->visibleCount = desc->visibleCount;
    list->totalCount = desc->totalCount;
    list->slotIndex = desc->slotIndex;
    list->arrowUpSlot = desc->arrowUpSlot;
    list->arrowDownSlot = desc->arrowDownSlot;
    list->barSlot = desc->barSlot;
    list->field1c = desc->field1c;
    list->field20 = desc->field20;
    list->field24 = desc->field24;
    list->field28 = desc->field28;
    list->scroll = 0;
    list->cursor = 0;
    if (list->barSlot >= 0) {
        rect = func_ov103_020bf8c0(list->id, list->barSlot, work);
        list->barSpan = rect->y - 0xf - rect->height;
        list->marginTop = 8;
        list->marginBottom = 8;
        list->field40 = 8;
        travel = F32_TO_FX32((float)(list->barSpan - (list->marginTop + list->marginBottom)));
        ratio = FX_Div_01ff9c84(F32_TO_FX32((float)list->visibleCount), F32_TO_FX32((float)list->totalCount));
        if (ratio > 0x1000) {
            ratio = 0x1000;
        }
        list->thumbLength = (int)(((s64)travel * ratio + 0x800) >> 12);
        list->thumbStep = (int)AlignUpTo4K_020beb00(FX_Div_01ff9c84(list->thumbLength, 0x8000)) >> 12;
    }
    if (list->arrowUpSlot >= 0) {
        func_ov103_020bf678(list->id, list->arrowUpSlot, 0, work);
    }
    if (list->totalCount <= list->visibleCount && list->arrowDownSlot >= 0) {
        func_ov103_020bf678(list->id, list->arrowDownSlot, 0, work);
    }
    func_ov103_020bfe7c(list->id, work);
}
