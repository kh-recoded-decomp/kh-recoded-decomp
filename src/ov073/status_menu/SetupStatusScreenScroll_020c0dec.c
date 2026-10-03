#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct ScrollList {
    s16 itemCount;
    u8 pad_02[0x22];
    s16 trackHeight;
} ScrollList;

typedef struct StatusMenu {
    u8 pad_0000[3];
    u8 flags;
    u8 pad_0004[0x10e0 - 4];
    ResourceContainer *container;
    u8 pad_10e4[0x10];
    ScrollList scroll;
} StatusMenu;

typedef struct StatusScreen {
    u16 entryCount;
    u8 pad_002[0x806];
    void *element;
} StatusScreen;

extern void SetupScrollList_020bdf10(ScrollList *list, ResourceContainer *container, BOOL enabled);
extern void func_ov027_020b9580(ResourceContainer *container, void *element, BOOL visible);

void SetupStatusScreenScroll_020c0dec(StatusMenu *menu, StatusScreen *screen)
{
    BOOL visible;

    menu->scroll.trackHeight = 0x30;
    menu->scroll.itemCount = screen->entryCount;
    SetupScrollList_020bdf10(&menu->scroll, menu->container, TRUE);
    visible = TRUE;
    if (!(menu->flags & 2)) {
        visible = FALSE;
    }
    func_ov027_020b9580(menu->container, screen->element, visible);
}
