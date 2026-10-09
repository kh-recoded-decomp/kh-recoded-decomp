#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

#define TO_FX32(v) ((fx32)(((f32)(v) > 0) ? (4096.0f * (f32)(v) + 0.5f) : (4096.0f * (f32)(v) - 0.5f)))

typedef struct {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
} ObjBounds;

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
} ListConfig;

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
    u8 pad_0000[0xD054];
    ListState lists[2];
} ViewerWork;

extern ObjBounds *GetSlotObjBounds_020c0acc(int screen, int slot, ViewerWork *work);
extern void SetSlotObjVisible_020c0820(int screen, int slot, int visible, ViewerWork *work);
extern void func_ov099_020c11b4(int screen, ViewerWork *work);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u32 AlignUpTo4K_020beb00(u32 size);

void InitScrollList_020c0b3c(ListConfig *config, ViewerWork *work)
{
    ListState *lists;
    ListState *list;
    int id;
    ObjBounds *bounds;
    fx32 travel;
    fx32 ratio;

    lists = work->lists;
    id = config->id;
    lists[id].id = id;
    list = &lists[id];
    list->pageSize = config->pageSize;
    list->itemCount = config->itemCount;
    list->cursorSlot = config->cursorSlot;
    list->upArrowSlot = config->upArrowSlot;
    list->downArrowSlot = config->downArrowSlot;
    list->barSlot = config->barSlot;
    list->thumbSlot = config->thumbSlot;
    list->firstItemSlot = config->firstItemSlot;
    list->lastItemSlot = config->lastItemSlot;
    list->barEndSlot = config->barEndSlot;
    list->scrollTop = 0;
    list->cursorRow = 0;
    if (list->barSlot >= 0) {
        bounds = GetSlotObjBounds_020c0acc(list->id, list->barSlot, work);
        list->trackHeight = bounds->maxY - 15 - bounds->minY;
        list->topMargin = 8;
        list->thumbWidth = 8;
        list->bottomMargin = 8;
        travel = TO_FX32(list->trackHeight - (list->topMargin + list->bottomMargin));
        ratio = FX_Div_01ff9c84(TO_FX32(list->pageSize), TO_FX32(list->itemCount));
        if (ratio > 0x1000) {
            ratio = 0x1000;
        }
        list->thumbLength = (fx32)(((s64)travel * ratio + 0x800) >> 12);
        list->thumbSteps = (int)AlignUpTo4K_020beb00(FX_Div_01ff9c84(list->thumbLength, 0x8000)) >> 12;
    }
    if (list->upArrowSlot >= 0) {
        SetSlotObjVisible_020c0820(list->id, list->upArrowSlot, FALSE, work);
    }
    if (list->itemCount <= list->pageSize && list->downArrowSlot >= 0) {
        SetSlotObjVisible_020c0820(list->id, list->downArrowSlot, FALSE, work);
    }
    func_ov099_020c11b4(list->id, work);
}
