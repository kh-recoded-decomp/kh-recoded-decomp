#ifndef RECODED_EU_STATUS_LIST_VIEW_H
#define RECODED_EU_STATUS_LIST_VIEW_H

#include "nitro/types.h"

typedef struct ListTouchSample {
    u16 x;
    u16 y;
    u16 touched;
    u16 validity;
} ListTouchSample;

typedef struct ListEntry {
    u16 unknown0;
    u16 column;
    u16 row;
    u16 unknown6;
} ListEntry;

typedef struct ListTable {
    u8 unknown0[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u32 unknown0;
    ListTable *table;
} ListData;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    u8 unknown08[0x94 - 8];
    s32 scrollX;
    s32 targetX;
    BOOL scrolling;
    BOOL cancelled;
    s32 cursorIndex;
    s32 selectedIndex;
    u8 unknownac[0x138 - 0xac];
    ListTouchSample previousTouch;
} ListView;

#define LIST_OFFSET(type, member) ((u32)&((type *)0)->member)
typedef char ListTouchSampleSizeCheck[sizeof(ListTouchSample) == 8 ? 1 : -1];
typedef char ListEntrySizeCheck[sizeof(ListEntry) == 8 ? 1 : -1];
typedef char ListViewSizeCheck[sizeof(ListView) == 0x140 ? 1 : -1];
typedef char ListTableCountOffsetCheck[LIST_OFFSET(ListTable, count) == 6 ? 1 : -1];
typedef char ListEntriesOffsetCheck[LIST_OFFSET(ListTable, entries) == 8 ? 1 : -1];
typedef char ListScrollOffsetCheck[LIST_OFFSET(ListView, scrollX) == 0x94 ? 1 : -1];
typedef char ListCursorOffsetCheck[LIST_OFFSET(ListView, cursorIndex) == 0xa4 ? 1 : -1];
typedef char ListSelectionOffsetCheck[LIST_OFFSET(ListView, selectedIndex) == 0xa8 ? 1 : -1];
typedef char ListPreviousTouchOffsetCheck[LIST_OFFSET(ListView, previousTouch) == 0x138 ? 1 : -1];
#undef LIST_OFFSET

void HandleListTouchInput(ListView *list, const ListTouchSample *touch);
void UpdateListScroll(ListView *list, const ListTouchSample *touch, u16 input);

#endif
