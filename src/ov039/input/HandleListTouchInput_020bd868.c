#include "nitro/types.h"

typedef union {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    };
} TouchPoint;

typedef struct {
    TouchPoint prev;
    TouchPoint point;
    u16 touchFlags;
} ListInput;

typedef struct {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
    u8 rowHeight;
    u8 pad_09[3];
    s32 smoothScroll;
    s32 layoutLocked;
    u8 pad_14[4];
    s32 cursorLocked;
    u8 dragState;
    u8 pad_1d[3];
    s16 touchedRow;
    u8 pad_22[2];
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    TouchPoint lastTouch;
    s16 grabOffset;
    u8 pad_32[2];
    s32 scrollPixels;
    s32 velocity;
    u8 trackRows;
    u8 entryCount;
} ScrollList;

extern void ClampScrollCursor_020bd694(ScrollList *list);
extern void SnapScrollToStep_020bd750(ScrollList *list, BOOL updateThumb);
extern BOOL UpdateScrollInertia_020bd7b0(ScrollList *list, void *owner, ListInput *input);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *owner);

static inline BOOL PointInList(ScrollList *list, TouchPoint p)
{
    return list->left <= p.x && p.x < list->right && list->top <= p.y && p.y < list->bottom;
}

static inline int ThumbOffset(ScrollList *list)
{
    return list->topIndex * list->rowHeight * ((list->trackRows - list->entryCount) * 8) / ((list->itemCount - list->visibleRows) * list->rowHeight);
}

static inline void ReleaseTouch(ScrollList *list, ListInput *input, TouchPoint *point)
{
    u8 flags = list->dragState;

    if (flags & 1) {
        if (flags & 8) {
            s16 top = list->top;
            int row = list->topIndex + (point->y - top + list->scrollPixels % list->rowHeight) / list->rowHeight;

            if (row >= list->topIndex + list->visibleRows) {
                row = list->topIndex + list->visibleRows - 1;
            }
            if (row < list->itemCount) {
                if (list->cursorLocked == 0) {
                    list->cursor = row;
                }
                list->touchedRow = list->scrollPixels + list->lastTouch.y - top;
            }
            list->dragState = 0;
        } else if (flags & 0x10) {
            list->dragState = flags & 0xEE;
            list->velocity += (point->y - input->prev.y) << 12;
            return;
        } else {
            SnapScrollToStep_020bd750(list, TRUE);
            list->dragState = 0;
        }
    } else {
        list->dragState = 0;
    }
}

BOOL HandleListTouchInput_020bd868(ScrollList *list, void *owner, ListInput *input, BOOL changed)
{
    TouchPoint point = input->point;
    BOOL scrollable = list->itemCount > list->visibleRows;
    u8 flags;

    changed |= UpdateScrollInertia_020bd7b0(list, owner, input);
    switch (input->touchFlags & 3) {
    case 0:
        break;
    case 1:
        if (!PointInList(list, point)) {
            break;
        }
        if (list->right - point.x < 16) {
            if (scrollable && list->top + 8 <= point.y && point.y < list->bottom - 8) {
                u16 thumbLen = list->entryCount * 8;
                u16 halfThumb = thumbLen >> 1;
                s16 trackLen = list->visibleRows * list->rowHeight - 16;
                s16 thumbTop;
                s16 trackTop;
                s16 pos;

                thumbTop = list->scrollOffset + list->topIndex * ((list->trackRows - list->entryCount) * 8) / (list->itemCount - list->visibleRows);
                trackTop = list->top + 8;
                thumbTop += trackTop;

                if (thumbTop <= point.y && point.y < thumbTop + thumbLen) {
                    list->grabOffset = point.y - thumbTop;
                } else {
                    s16 rel = point.y - trackTop;

                    if (point.y < thumbTop) {
                        list->grabOffset = rel < halfThumb ? rel : halfThumb;
                    } else {
                        list->grabOffset = rel + halfThumb >= trackLen ? thumbLen - (trackLen - rel) : halfThumb;
                    }
                }
                pos = point.y - list->grabOffset - trackTop;
                list->scrollPixels = (u32)(pos * ((list->itemCount - list->visibleRows) * list->rowHeight)) / (u32)(trackLen - thumbLen);
                ClampScrollCursor_020bd694(list);
                list->scrollOffset = pos - ThumbOffset(list);
                list->dragState |= 5;
            }
        } else if (list->dragState == 2) {
            list->dragState |= 0x11;
        } else {
            int row;

            list->dragState |= 9;
            list->scrollPixels = list->topIndex * list->rowHeight;
            row = list->topIndex + (point.y - list->top + list->scrollPixels % list->rowHeight) / list->rowHeight;
            if (list->cursorLocked == 0 && row < list->itemCount) {
                list->cursor = row;
            }
            list->touchedRow = list->scrollPixels + list->lastTouch.y - list->top;
            ClampScrollCursor_020bd694(list);
        }
        list->lastTouch = point;
        changed = TRUE;
        break;
    case 3:
        flags = list->dragState;
        if (!(flags & 1)) {
            break;
        }
        if ((list->left <= point.x && point.x < list->right) || (flags & 4)) {
            BOOL exact;
            int range;
            u16 thumbLen;
            s16 trackLen;
            u32 span;
            s16 pos;

            if (flags & 8) {
                s16 delta;
                s16 sign;

                list->touchedRow = -1;
                delta = point.y - list->lastTouch.y;
                sign = delta >> 15;
                if ((u16)((delta ^ sign) - sign) > 4) {
                    if (list->visibleRows < list->itemCount) {
                        list->dragState = (list->dragState & ~8) | 0x12;
                        list->velocity = (point.y - input->prev.y) << 12;
                    } else {
                        list->dragState = 0;
                    }
                }
            }
            if (list->dragState & 0x10) {
                list->velocity += (point.y - input->prev.y) << 12;
            }
            if (!(list->dragState & 4)) {
                break;
            }
            exact = FALSE;
            range = (list->itemCount - list->visibleRows) * list->rowHeight;
            thumbLen = list->entryCount * 8;
            trackLen = list->trackRows * 8;
            span = trackLen - thumbLen;
            pos = list->top + 8;
            pos = point.y - list->grabOffset - pos;
            if (pos < 0) {
                list->scrollPixels = 0;
            } else if (pos + thumbLen > trackLen) {
                list->scrollPixels = range;
            } else {
                list->scrollPixels = (u32)(pos * range) / span;
                exact = TRUE;
            }
            ClampScrollCursor_020bd694(list);
            if (exact) {
                list->scrollOffset = pos - ThumbOffset(list);
            } else {
                list->scrollOffset = 0;
            }
            changed = TRUE;
            break;
        }
    case 2:
        ReleaseTouch(list, input, &point);
        changed = TRUE;
        break;
    }
    if (changed && list->layoutLocked == 0) {
        RefreshScrollListLayout_020be138(list, owner);
    }
    return changed;
}
