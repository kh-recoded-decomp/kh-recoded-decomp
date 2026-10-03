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

extern char data_ov077_020ca2f8[];
extern SaveData *data_0205fe0c;
extern void NotifyBothOrOne_02001154(u32 a, u32 b, int index);
extern void SetStateFlagBits_020bc688(int clearMask, int setBits);
extern void SetFlagGatedElementsVisible_020c9d7c(void *container, BOOL visible);
extern void SetContainerElementVisible_020c9d1c(void *container, int elementId, BOOL visible);
extern void SetupStageParams_020bdf10(void *listView, void *layout, int mode);
extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);

void MenuPanel_CloseItemList_020c6c90(ItemListMenu *menu, BOOL closing)
{
    void *layout = menu->layout;
    u32 *src;
    u32 *dst;
    u32 *end;

    NotifyBothOrOne_02001154(1, (u32)data_ov077_020ca2f8, 0);
    SetStateFlagBits_020bc688(0xf, menu->stateFlags);
    SetFlagGatedElementsVisible_020c9d7c(layout, closing);
    SetContainerElementVisible_020c9d1c(layout, 7, FALSE);
    SetContainerElementVisible_020c9d1c(layout, 0x1b, FALSE);
    SetContainerElementVisible_020c9d1c(layout, 0x1c, FALSE);
    SetContainerElementVisible_020c9d1c(layout, 0, FALSE);
    SetContainerElementVisible_020c9d1c(layout, 1, FALSE);
    SetupStageParams_020bdf10(menu->listView, layout, 0);
    menu->interactive = !closing;
    REG_BG1OFS = 0;
    if (closing) {
        CallStateWidget_020bc14c(9, 0, 0, 0x20, 0x18);
    }
    src = menu->pendingUnlocks;
    dst = data_0205fe0c->unlockFlags;
    end = dst + 0x10;
    for (; dst < end; src++, dst++) {
        *dst |= *src;
    }
}


