#ifndef KH_RECODED_OV025_SLOT_LIST_TOUCH_H
#define KH_RECODED_OV025_SLOT_LIST_TOUCH_H

#include "nitro/types.h"

typedef struct ListTouchInput {
    u16 x;
    u16 y;
    u16 down;
    u16 status;
} ListTouchInput;

typedef struct ListTouchRow {
    u16 value;
    u16 tileX;
    u16 tileY;
    u16 reserved06;
} ListTouchRow;

typedef struct ListTouchRowTable {
    u8 reserved00[6];
    u16 count;
    ListTouchRow rows[];
} ListTouchRowTable;

typedef struct ListTouchData {
    u8 reserved00[4];
    ListTouchRowTable *table;
} ListTouchData;

typedef struct ListTouchView {
    u8 reserved00[4];
    ListTouchData *data;
    u8 reserved08[0x8c];
    s32 scrollPos;
    s32 scrollTarget;
    BOOL scrolling;
    s32 busy;
    s32 cursorIndex;
    s32 selectedIndex;
    u8 reservedac[0x8c];
    ListTouchInput previousTouch;
} ListTouchView;

typedef char ListTouchInputSizeCheck[sizeof(ListTouchInput) == 8 ? 1 : -1];
typedef char ListTouchRowSizeCheck[sizeof(ListTouchRow) == 8 ? 1 : -1];
typedef char ListTouchHistoryOffsetCheck[
    (u32)&((ListTouchView *)0)->previousTouch == 0x138 ? 1 : -1];

void HandleListTouch(ListTouchView *list, const ListTouchInput *touch);

#endif
