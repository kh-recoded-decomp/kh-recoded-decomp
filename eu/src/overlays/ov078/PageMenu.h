#ifndef KH_RECODED_PAGE_MENU_H
#define KH_RECODED_PAGE_MENU_H

#include "nitro/types.h"

typedef struct PageSlot {
    s16 recordId;
    u8 level;
    u8 rank;
} PageSlot;

typedef struct PageTableEntry {
    u8 reserved00[2];
    PageSlot details[3];
    PageSlot headers[3];
} PageTableEntry;

typedef struct PageMenu {
    void *buffers[3];
    int messageView[3];
    int headerMessageView[3];
    void *nodes[8];
    u8 reserved44[0xc];
    u8 charBuffer[0x580];
    int cursor;
    int page;
} PageMenu;

void DrawPageDetails(PageMenu *menu);

#endif
