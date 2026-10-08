#include "nitro/types.h"

#define REG_BG1OFS (*(volatile u32 *)0x04000014)

typedef struct SaveData {
    u8 pad_0000[0x2bd8];
    u32 unlockFlags[0x10];
} SaveData;

typedef struct ItemListMenu {
    u32 state;
    BOOL interactive;
    u8 pad_0008[0x10];
    void *layout;
    u8 pad_001c[0x4d84 - 0x1c];
    u8 listView[0x11e60 - 0x4d84];
    u16 stateFlags;
    u16 pad_11e62;
    u32 pendingUnlocks[0x10];
} ItemListMenu;

extern char sOv076_ScrollCmx_020cd37c[];
extern SaveData *data_0205fe0c;
extern void NotifyBothOrOne(u32 a, u32 b, int index);
extern void SetStateFlagBits(int clearMask, int setBits);
extern void SetNavigationElementsVisible(void *container, BOOL visible);
extern void SetContainerElementVisible(void *container, int elementId, BOOL visible);
extern void func_ov034_020bdf30(void *listView, void *layout, int mode);
extern void CallStateWidget(int a, int b, int c, int d, int e);

void SlotMenu_CloseItemList(ItemListMenu *menu, BOOL closing)
{
    void *layout = menu->layout;
    u32 *src;
    u32 *dst;
    u32 *end;

    NotifyBothOrOne(1, (u32)sOv076_ScrollCmx_020cd37c, 0);
    SetStateFlagBits(0xf, menu->stateFlags);
    SetNavigationElementsVisible(layout, closing);
    SetContainerElementVisible(layout, 7, FALSE);
    SetContainerElementVisible(layout, 0x1b, FALSE);
    SetContainerElementVisible(layout, 0x1c, FALSE);
    SetContainerElementVisible(layout, 0, FALSE);
    SetContainerElementVisible(layout, 1, FALSE);
    func_ov034_020bdf30(menu->listView, layout, 0);
    menu->interactive = !closing;
    REG_BG1OFS = 0;
    if (closing) {
        CallStateWidget(9, 0, 0, 0x20, 0x18);
    }
    src = menu->pendingUnlocks;
    dst = data_0205fe0c->unlockFlags;
    end = dst + 0x10;
    for (; dst < end; src++, dst++) {
        *dst |= *src;
    }
}
