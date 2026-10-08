#include "nitro/types.h"

typedef struct ScrollList {
    s8 itemCount;
    s8 visibleCount;
    s8 rowInView;
    s8 scrollOffset;
    s8 cursor;
    u8 flags;
    u8 pad_06[2];
    int scrollPixels;
    int maxScrollPixels;
    int rowPixels;
    int rowHeight;
} ScrollList;

void SetScrollListPixels(ScrollList *list, int pixels, BOOL keepCursor)
{
    int previous = list->scrollPixels;
    int limit;

    list->scrollPixels = pixels;
    list->scrollOffset = pixels / list->rowHeight;
    if (keepCursor) {
        list->rowPixels -= pixels - previous;
    }
    if (list->rowPixels < 0) {
        list->rowPixels = 0;
    } else {
        limit = (list->visibleCount - 1) * list->rowHeight;
        if (list->rowPixels > limit) {
            list->rowPixels = limit;
        }
    }
    list->rowInView = (list->rowPixels + list->scrollPixels + list->rowHeight / 2) / list->rowHeight - list->scrollOffset;
    list->cursor = list->rowInView + list->scrollOffset;
}
