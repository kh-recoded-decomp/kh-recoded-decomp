#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rect16;

typedef struct {
    int handle;
    int x;
    int y;
    u8 pad_0C[8];
    Rect16 bounds;
} SlotItem;

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    u8 pad_0C[0x20];
    int scrollPos;
    u8 pad_30[0x1c];
} ScrollBar;

typedef struct {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
    Rect16 track;
    int grabbed;
    int unk_14;
    int dragDelta;
    int dragStartY;
    int dragCurrentY;
    int dragStartPos;
    int lastY;
    int prevY;
    int flinging;
    int flingTarget;
} DragArea;

typedef struct {
    u8 pad_0000[0xcbd4];
    SlotItem items[13];
    u8 pad_cd40[0xcf54 - 0xcd40];
    ScrollBar bars[2];
    u8 pad_cfec[0xd1c4 - 0xcfec];
    int touchActive;
    u8 pad_d1c8[0xd1ec - 0xd1c8];
    DragArea drag;
} SceneWork;

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

extern SceneWork *g_sceneWork_020c50e0;

extern TouchState *func_ov039_020bca00(void);
extern void func_ov093_020c21f8(int index);
extern int GetSmoothValueInt_020c21d8(int index);
extern void func_ov093_020c0cb0(int index, SceneWork *work);
extern void func_ov093_020bfd60(int index, SceneWork *work);
extern void func_ov093_020c05b8(SceneWork *work);
extern void func_ov093_020c2254(int index);
extern void ResetSmoothValue_020c2058(int index);
extern void func_ov093_020c2080(int index, int value);
extern void func_ov093_020c2158(int index, int value);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

void UpdateScrollBarDrag_020c1d48(void)
{
    SceneWork *work = g_sceneWork_020c50e0;
    DragArea *drag = &work->drag;
    ScrollBar *bar = &work->bars[1];
    TouchState *touch = func_ov039_020bca00();
    SlotItem *lowerItem;
    SlotItem *upperItem;
    int halfHeight;
    int top;
    int bottom;
    int y;
    fx32 ratio;
    int maxPos;

    lowerItem = &work->items[2];
    upperItem = &work->items[3];
    drag->track.right = lowerItem->x + lowerItem->bounds.right;
    drag->track.bottom = lowerItem->y + lowerItem->bounds.bottom;
    drag->track.left = lowerItem->x + lowerItem->bounds.left;
    drag->track.top = upperItem->y + upperItem->bounds.top;

    if (((touch->state & 3) == 0 || (touch->state & 3) == 2) && drag->flinging != 0) {
        func_ov093_020c21f8(0);
        bar->scrollPos = GetSmoothValueInt_020c21d8(0);
        func_ov093_020c0cb0(1, work);
        func_ov093_020bfd60(1, work);
        func_ov093_020c05b8(work);
        func_ov093_020c2254(0);
    }

    if ((touch->state & 3) == 0) {
        return;
    }
    if ((touch->state & 3) == 1) {
        if (drag->minX <= touch->x && touch->x <= drag->maxX && drag->minY <= touch->y && touch->y <= drag->maxY) {
            drag->grabbed = 1;
        }
    }
    if ((touch->state & 3) == 2) {
        drag->grabbed = 0;
        drag->unk_14 = 0;
        drag->dragDelta = 0;
        drag->dragStartY = 0;
        drag->dragCurrentY = 0;
        drag->dragStartPos = 0;
        work->touchActive = 0;
        return;
    }
    if (drag->grabbed != 0) {
        if (touch->state & 1) {
            halfHeight = (drag->track.top - drag->track.bottom) / 2;
            bottom = drag->minY + halfHeight;
            top = drag->maxY - halfHeight;
            work->touchActive = 1;
            drag->flinging = 0;
            y = touch->y;
            if (y > top) {
                y = top;
            }
            y -= bottom;
            if (y < 0) {
                y = 0;
            }
            ratio = FX_Div_01ff9c84(y << 12, (top - bottom) << 12);
            bar->scrollPos = (FxMul((bar->rangeEnd - bar->rangeStart) << 12, ratio) + 0x800) >> 12;
            func_ov093_020c0cb0(1, work);
            func_ov093_020bfd60(1, work);
            func_ov093_020c05b8(work);
        }
        return;
    }
    if ((touch->state & 3) == 1) {
        work->touchActive = 1;
        drag->dragStartY = touch->y;
        drag->dragStartPos = bar->scrollPos;
        drag->lastY = touch->y;
        drag->flinging = 0;
        ResetSmoothValue_020c2058(0);
    }
    if ((touch->state & 3) == 3) {
        drag->dragCurrentY = touch->y;
        drag->dragDelta = drag->dragCurrentY - drag->dragStartY;
        bar->scrollPos = drag->dragStartPos - drag->dragDelta / 16;
        if (bar->scrollPos < 0) {
            bar->scrollPos = 0;
        }
        maxPos = bar->rangeEnd - bar->rangeStart;
        if (bar->scrollPos > maxPos) {
            bar->scrollPos = maxPos;
        }
        func_ov093_020c0cb0(1, work);
        func_ov093_020bfd60(1, work);
        func_ov093_020c05b8(work);
        drag->prevY = drag->lastY;
        drag->lastY = touch->y;
        drag->flingTarget = bar->scrollPos - (drag->lastY - drag->prevY) * 9 / 8;
        drag->flinging = 1;
        if (drag->flingTarget < 0) {
            drag->flingTarget = 0;
        }
        maxPos = bar->rangeEnd - bar->rangeStart;
        if (drag->flingTarget > maxPos) {
            drag->flingTarget = maxPos;
        }
        func_ov093_020c2080(0, bar->scrollPos);
        func_ov093_020c2158(0, drag->flingTarget);
    }
}
