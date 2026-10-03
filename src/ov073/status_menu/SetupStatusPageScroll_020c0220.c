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

typedef struct StatusPage {
    u8 rowCount;
    u8 pad_01[0xb3];
    void *element;
} StatusPage;

extern void SetupScrollList_020bdf10(ScrollList *list, ResourceContainer *container, BOOL enabled);
extern void func_ov039_020bc914(void);
extern void func_ov027_020b9580(ResourceContainer *container, void *element, BOOL visible);

void SetupStatusPageScroll_020c0220(StatusMenu *menu, StatusPage *page)
{
    BOOL visible;

    func_ov039_020bc914();
    menu->scroll.trackHeight = 0xd8;
    menu->scroll.itemCount = page->rowCount;
    SetupScrollList_020bdf10(&menu->scroll, menu->container, TRUE);
    visible = TRUE;
    if (!(menu->flags & 2)) {
        visible = FALSE;
    }
    func_ov027_020b9580(menu->container, page->element, visible);
}
