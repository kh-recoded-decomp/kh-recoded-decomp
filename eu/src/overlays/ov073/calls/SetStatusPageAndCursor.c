#include "nitro/types.h"

typedef struct MenuSharedState MenuSharedState;

typedef struct PageHandler {
    void (*enter)(MenuSharedState *state, void *arg);
    u8 pad_04[8];
    void (*leave)(MenuSharedState *state, void *arg);
    void *arg;
} PageHandler;

typedef struct ItemEntry {
    u16 count;
    u8 pad_02[2];
    int itemId;
    u8 pad_08[0x18];
} ItemEntry;

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 visibleRows;
} ScrollList;

struct MenuSharedState {
    s8 page;
    u8 dirty;
    u8 refreshCount;
    u8 flags;
    u8 pad_004[0x250 - 0x004];
    ItemEntry items[(0xd50 - 0x250) / 0x20];
    PageHandler pages[5];
    u8 pad_db4[0x10e0 - 0xdb4];
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    ScrollList list;
};

extern MenuSharedState *GetMenuSharedState(void);
extern void ResetStatusPageState(MenuSharedState *state);
extern void RefreshScrollListLayout(ScrollList *list, void *container);

void SetStatusPageAndCursor(int page, int index)
{
    MenuSharedState *state = GetMenuSharedState();
    PageHandler *handler;
    int slot;
    ItemEntry *items;

    if (page != state->page) {
        if (state->page == 4 || page == 4) {
            state->refreshCount = 1;
        }
        handler = &state->pages[state->page];
        handler->leave(state, handler->arg);
        handler = &state->pages[page];
        state->page = page;
        ResetStatusPageState(state);
        handler->enter(state, handler->arg);
        state->dirty = TRUE;
    }
    if (index < 0) {
        return;
    }
    if (page == 2) {
        items = state->items;
        switch (index) {
        case 0xf8:
        case 0xf9:
        case 0xfa:
        case 0xfb:
            index = 9;
            break;
        case 0xfc:
        case 0xfd:
            index = 10;
            break;
        case 0xfe:
        case 0xff:
        case 0x100:
            index = 0xd;
            break;
        case 0x101:
        case 0x102:
            index = 0xe;
            break;
        case 0x103:
        case 0x104:
            index = 0x10;
            break;
        case 0x105:
        case 0x106:
        case 0x107:
            index = 0x12;
            break;
        case 0x108:
        case 0x109:
        case 0x10a:
            index = 0x13;
            break;
        case 0x10b:
        case 0x10c:
            index = 0x14;
            break;
        }
        for (slot = 0; slot < items->count; slot++) {
            if (index == items[slot].itemId) {
                break;
            }
        }
    } else {
        slot = index;
    }
    if (slot >= 0 && slot < state->list.itemCount) {
        state->list.cursor = slot;
        if (slot >= state->list.visibleRows) {
            state->list.topIndex = slot - state->list.visibleRows + 1;
        } else {
            state->list.topIndex = 0;
        }
        RefreshScrollListLayout(&state->list, state->container);
        state->dirty = TRUE;
    }
}
