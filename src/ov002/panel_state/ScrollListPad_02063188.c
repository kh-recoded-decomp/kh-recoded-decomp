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
    int unk_0C;
    int rowPixels;
    int rowHeight;
} ScrollList;

extern u32 UpdateListCursorPad_02062f88(void *input, ScrollList *list);

u32 ScrollListPad_02063188(void *input, ScrollList *list)
{
    u32 result = UpdateListCursorPad_02062f88(input, list);
    list->scrollPixels = list->scrollOffset * list->rowHeight;
    list->rowPixels = list->rowInView * list->rowHeight;
    return result;
}
