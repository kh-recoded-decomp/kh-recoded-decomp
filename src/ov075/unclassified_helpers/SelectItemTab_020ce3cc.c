#include "nitro/types.h"

typedef struct ItemMenu {
    u8 pad_0000[0x18];
    void *objManager;
    u8 pad_001c[4];
    u16 tab;
    u8 pad_0022[0x4d78 - 0x22];
    u16 itemCount;
    u8 pad_4d7a[0x4d84 - 0x4d7a];
    u16 visibleCount;
    s16 selected;
    s16 scrollTop;
} ItemMenu;

extern u16 BuildTabItemList_020cde04(ItemMenu *menu, int tab);
extern void PlaySoundEffect_0204d924(int channel, int id);
extern int FindWidgetById_020b90a4(void *manager, int elementId);
extern void func_ov027_020b96a0(void *manager, int element, u16 frame);
extern void func_ov075_020cdf88(ItemMenu *menu);

BOOL SelectItemTab_020ce3cc(ItemMenu *menu, int tab)
{
    BOOL changed;

    if ((menu->tab != tab && BuildTabItemList_020cde04(menu, tab) != 0) || tab == 1) {
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    if (changed) {
        PlaySoundEffect_0204d924(1, 2);
        menu->tab = tab;
        menu->visibleCount = menu->itemCount;
        menu->selected = 0;
        menu->scrollTop = menu->selected;
        func_ov027_020b96a0(menu->objManager, FindWidgetById_020b90a4(menu->objManager, 0x1b), tab);
        func_ov075_020cdf88(menu);
    } else {
        PlaySoundEffect_0204d924(1, 4);
    }
    return changed;
}